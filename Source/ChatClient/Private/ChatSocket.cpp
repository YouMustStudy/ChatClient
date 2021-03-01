// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatSocket.h"

// Sets default values
AChatSocket::AChatSocket()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	setlocale(LC_ALL, "Korean");
}

bool AChatSocket::ConnectServer()
{
	m_socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	FString address = TEXT("127.0.0.1");
	int32 port = 15600;
	FIPv4Address ip;
	FIPv4Address::Parse(address, ip);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Trying to connect.")));

	bool connected = m_socket->Connect(*addr);
	if (true == connected)
	{
		m_online = true;
		m_threads.emplace_back(&AChatSocket::recvThread, this);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Success connect.")));
	}
	else
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Fail connect.")));

	return connected;
}
void AChatSocket::SendMsg(UPARAM(ref) FString& msg)
{
    size_t convertedNum;
	msg.Append("\r\n");
    wcstombs_s<BUF_SIZE>(&convertedNum, m_mbcsBuffer, *msg, BUF_SIZE);
    if (0 != convertedNum)
    {
        int sendLength = 0;
        m_socket->Send(reinterpret_cast<const uint8*>(m_mbcsBuffer), strlen(m_mbcsBuffer), sendLength);
    }
};

void AChatSocket::recvThread()
{
	TCHAR utf16buffer[BUF_SIZE];
	size_t convertedNum=0;
	uint8 buffer[BUF_SIZE + 1];
	string data;
	while (true == m_online)
	{
		int32 readLength= 0;
		m_socket->Recv(buffer, BUF_SIZE, readLength);
		buffer[readLength] = 0;
		data.append(reinterpret_cast<const char*>(buffer));

		while (true)
		{
			int32 detPos = data.find("\r\n");
			if (string::npos != detPos)
			{
				mbstowcs_s<BUF_SIZE>(&convertedNum, utf16buffer, data.substr(0, detPos).c_str(), BUF_SIZE);
				m_recvQueue.Enqueue(utf16buffer);
				data = data.substr(detPos + 2);
			}
			else break;
		}
	}
}

// Called when the game starts or when spawned
void AChatSocket::BeginPlay()
{
	Super::BeginPlay();
}

void AChatSocket::BeginDestroy()
{
    Super::BeginDestroy();
	m_online = false;
    if (nullptr != m_socket)
        m_socket->Close();
	for (auto& thread : m_threads)
		thread.join();
}

constexpr int32 errLen = 4;
// Called every frame
void AChatSocket::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (true == m_online)
	{
		FString data;
		while (false == m_recvQueue.IsEmpty())
		{
			while (false == m_recvQueue.Dequeue(data)) {};
			if (true == data.StartsWith(L"[로그인]"))
			{
				ChangeToLobby();
			}
			else if (true == data.StartsWith(L"[에러]"))
			{
				AddErrorLog(data.Mid(errLen));
			}
			else
			{
				AddChatLog(data);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, data);
			}
		}
	}
}