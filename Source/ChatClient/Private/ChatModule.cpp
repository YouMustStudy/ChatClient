// Fill out your copyright notice in the Description page of Project Settings.
#include "ChatModule.h"

// Sets default values
AChatModule::AChatModule()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//코드페이지 한글 명시
	setlocale(LC_ALL, "Korean");
}

bool AChatModule::ConnectServer(const FString& address, int32 port)
{
	//포트범위 벗어나면 에러처리.
	if (port < 0 ||
		port > USHRT_MAX)
		return false;

	m_socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	if (nullptr != m_socket)
	{
		FIPv4Address ip;
		FIPv4Address::Parse(address, ip);

		TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
		addr->SetIp(ip.Value);
		addr->SetPort(port);

		bool connected = m_socket->Connect(*addr);
		if (true == connected)
		{
			m_online = true;
			m_threads.emplace_back(&AChatModule::recvThread, this);
		}

		return connected;
	}
	return false;
}
void AChatModule::SendMsg(UPARAM(ref) const FString& msg)
{
	//서버로 메세지를 전송하는 함수
	size_t convertedNum;
	FString completeMsg = msg + m_commands[static_cast<uint8>(CMD_TYPE::SUFFIX)];
	wcstombs_s<BUF_SIZE>(&convertedNum, m_mbcsBuffer, *completeMsg, BUF_SIZE);
	if (0 != convertedNum)
	{
		int sendLength = 0;
		if (nullptr != m_socket)
		{
			m_socket->Send(reinterpret_cast<const uint8*>(m_mbcsBuffer), strlen(m_mbcsBuffer), sendLength);
		}
	}
};

void AChatModule::recvThread()
{
	TCHAR utf16buffer[BUF_SIZE];
	size_t convertedNum = 0;
	uint8 buffer[BUF_SIZE + 1];
	string data;
	char suffixStamp = 5;
	string suffix = string("\r\n") + suffixStamp;
	while (true == m_online)
	{
		int32 readLength = 0;
		if (nullptr != m_socket)
		{
			if (false == m_socket->Recv(buffer, BUF_SIZE, readLength))
				return;

			buffer[readLength] = 0;
			data.append(reinterpret_cast<const char*>(buffer));

			//문자열 종결 시 처리부로 넘김.
			while (true)
			{
				int32 detPos = data.find(suffix);
				if (string::npos != detPos)
				{
					mbstowcs_s<BUF_SIZE>(&convertedNum, utf16buffer, data.substr(0, detPos).c_str(), BUF_SIZE);
					m_recvQueue.Enqueue(utf16buffer);
					data = data.substr(detPos + suffix.size());
				}
				else break;
			}
		}
	}
}

// Called when the game starts or when spawned
void AChatModule::BeginPlay()
{
	Super::BeginPlay();

	//ui생성 후 등록
	if (nullptr == uiTotal)
	{
		FString path = FString("/Game/UI/UI_TOTAL.UI_TOTAL_C");
		UClass* TotalClass = ConstructorHelpersInternal::FindOrLoadClass(path, UUserWidget::StaticClass());
		uiTotal = CreateWidget<UCUI_TOTAL>(GetWorld(), TotalClass);
		if (nullptr != uiTotal)
		{
			//UI 생성
			uiTotal->AddToViewport();
			uiTotal->InitUI(this);

			//포커스 설정
			auto controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (nullptr != controller)
			{
				FInputModeUIOnly param;
				param.SetWidgetToFocus(uiTotal->GetCachedWidget());
				controller->SetInputMode(param);
				controller->bShowMouseCursor = true;
			}
		}
	}

	//커맨드에 해당되는 문자열 생성.
	m_commands.Add(L"[로그인]");
	m_commands.Add(L"[에러]");
	m_commands.Add(L"[방입장]");
	m_commands.Add(L"[방 목록]");
	m_commands.Add(L"[유저목록]");
	m_commands.Add(L"[유저입장]");
	m_commands.Add(L"[유저퇴장]");
	m_commands.Add(L"[도움말]");
	m_commands.Add(L"[메세지]");
	m_commands.Add(L"\r\n");
}

void AChatModule::BeginDestroy()
{
	Super::BeginDestroy();
	Disconnect();
	for (auto& thread : m_threads)
		thread.join();
	m_threads.clear();
}

void AChatModule::Disconnect()
{
	if (true == m_online)
	{
		m_online = false;
		if (nullptr != m_socket)
		{
			m_socket->Close();
			m_socket = nullptr;

			if (nullptr != uiTotal)
			{
				uiTotal->ChangeSceneTo(SC_TYPE::LOGIN);
				uiTotal->PopError("서버와의 연결이 종료되었습니다.");
			}
		}
	}
}

// Called every frame
void AChatModule::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (true == m_online)
	{
		FString data;
		while (false == m_recvQueue.IsEmpty())
		{
			if (nullptr == uiTotal) continue;

			while (false == m_recvQueue.Dequeue(data)) {};

			if (true == data.StartsWith(m_commands[static_cast<uint8>(CMD_TYPE::LOGIN)]))
			{
				//로그인 성공 시 메인화면으로 전환.
				uiTotal->ChangeSceneTo(SC_TYPE::MAIN);
			}
			else if (true == data.StartsWith(m_commands[static_cast<uint8>(CMD_TYPE::ERROR)]))
			{
				//에러메세지 수신 시 에러창 팝업
				uiTotal->PopError(data.Mid(m_commands[static_cast<uint8>(CMD_TYPE::ERROR)].Len()));
			}
			else if (true == data.StartsWith(m_commands[static_cast<uint8>(CMD_TYPE::ROOMENTER)]))
			{
				//방 입장 성공 시 메인화면으로 전환.
				uiTotal->EnterRoom(data.Mid(m_commands[static_cast<uint8>(CMD_TYPE::ROOMENTER)].Len()));

			}
			else if (true == data.StartsWith(m_commands[static_cast<uint8>(CMD_TYPE::ROOMLIST)]))
			{
				//방목록 수신 시 갱신 및 방목록 화면으로 전환
				TArray<FString> rooms;
				data.Mid(m_commands[static_cast<uint8>(CMD_TYPE::ROOMLIST)].Len()).ParseIntoArray(rooms, *m_commands[static_cast<uint8>(CMD_TYPE::SUFFIX)]);
				uiTotal->EnterRoomList(rooms);
			}
			else if (true == data.StartsWith(m_commands[static_cast<uint8>(CMD_TYPE::USERLIST)]))
			{
				//유저목록 수신 시 목록 갱신
				TArray<FString> users;
				data.Mid(m_commands[static_cast<uint8>(CMD_TYPE::USERLIST)].Len()).ParseIntoArray(users, *m_commands[static_cast<uint8>(CMD_TYPE::SUFFIX)]);
				uiTotal->RefreshUserBox(users);
			}
			else if (true == data.StartsWith(m_commands[static_cast<uint8>(CMD_TYPE::USERENTER)]))
			{
				//유저 입장 송신 시 목록 추가 및 메세지 출력
				uiTotal->AddUserBox(data.Mid(m_commands[static_cast<uint8>(CMD_TYPE::USERENTER)].Len()));
				uiTotal->AddChatLog(TArray<FString>{data});
			}
			else if (true == data.StartsWith(m_commands[static_cast<uint8>(CMD_TYPE::USERLEAVE)]))
			{
				//유저 퇴장 송신 시 목록 제거 및 메세지 출력
				uiTotal->RemoveUserBox(data.Mid(m_commands[static_cast<uint8>(CMD_TYPE::USERLEAVE)].Len()));
				uiTotal->AddChatLog(TArray<FString>{data});
			}
			else if (true == data.StartsWith(m_commands[static_cast<uint8>(CMD_TYPE::HELP)]))
			{
				//도움말 송신 시 출력
				uiTotal->PopError(data.Mid(m_commands[static_cast<uint8>(CMD_TYPE::HELP)].Len() + m_commands[static_cast<uint8>(CMD_TYPE::SUFFIX)].Len()));
			}
			else if (true == data.StartsWith(m_commands[static_cast<uint8>(CMD_TYPE::MSG)]))
			{
				//귓속말 출력
				TArray<FString> msgs;
				data.ParseIntoArray(msgs, *m_commands[static_cast<uint8>(CMD_TYPE::SUFFIX)]);
				uiTotal->AddChatLog(msgs, FLinearColor(0.5, 0.5, 1.0, 1.0));
			}
			else
			{
				//채팅메세지 출력
				TArray<FString> msgs;
				data.ParseIntoArray(msgs, *m_commands[static_cast<uint8>(CMD_TYPE::SUFFIX)]);
				uiTotal->AddChatLog(msgs);
			}
		}
	}
}