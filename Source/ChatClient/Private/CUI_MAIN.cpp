// Fill out your copyright notice in the Description page of Project Settings.
#include "CUI_MAIN.h"
#include "CUI_LOG.h"
#include "CUI_USER.h"
#include "ChatModule.h"

void UCUI_MAIN::RequestRoomList()
{
	//방목록 갱신을 요청
	static FString roomListCommand = L"/roomlist";
	if (nullptr != chatModule)
	{
		chatModule->SendMsg(roomListCommand);
	}
}

void UCUI_MAIN::NativeConstruct()
{
	Super::NativeConstruct();
	if(nullptr != sendButton)
		sendButton->OnClicked.AddDynamic(this, &UCUI_MAIN::SendChat);
	if(nullptr != roomButton)
		roomButton->OnClicked.AddDynamic(this, &UCUI_MAIN::RequestRoomList);
}

void UCUI_MAIN::SetRoomName(const FString& name)
{
	//이름 설정
	if (nullptr != roomNameText)
		roomNameText->SetText(FText::FromString(name));
}

void UCUI_MAIN::ClearInputMsgBox()
{
	//입력박스 초기화
	if (nullptr != inputMsgBox)
		inputMsgBox->SetText(FText::GetEmpty());
}

void UCUI_MAIN::SendChat()
{
	if (nullptr != inputMsgBox)
	{
		//유저의 입력을 받아 서버에 전송.
		FString msg = inputMsgBox->GetText().ToString();
		if (false == msg.IsEmpty())
		{
			if (nullptr != chatModule)
			{
				chatModule->SendMsg(msg);
				inputMsgBox->SetText(FText::GetEmpty());
				inputMsgBox->SetKeyboardFocus();
			}
		}
	}
}

void UCUI_MAIN::SetInputMsgBox(const FString& msg)
{
	if (nullptr != inputMsgBox)
	{
		//주어진 문자열로 입력창을 초기화.
		inputMsgBox->SetText(FText::FromString(msg));
		inputMsgBox->SetKeyboardFocus();
	}
}

void UCUI_MAIN::AddChatLog(UPARAM(ref) const FString& msg)
{
	if (nullptr != chatBox)
	{
		//채팅 로그가 MAX_CHAT_LOG를 넘어가면 맨 앞 객체를 삭제 후 삽입.
		int32 chatLogCnt = chatBox->GetChildrenCount();
		if (chatLogCnt >= MAX_CHAT_LOG)
			chatBox->RemoveChildAt(0);

		UCUI_LOG* UILog = CreateWidget<UCUI_LOG>(GetWorld(), UILogClass.Get());
		if (nullptr != UILog)
		{
			int32 curOffset = chatBox->GetScrollOffset();
			int32 endOffset = chatBox->GetScrollOffsetOfEnd();
			UILog->chatLog->SetText(FText::FromString(msg));
			chatBox->AddChild(UILog);
			if (curOffset == endOffset)
				chatBox->ScrollToEnd();
		}
	}
}

void UCUI_MAIN::ClearChatLog()
{
	//채팅로그를 초기화
	if(nullptr != chatBox)
		chatBox->ClearChildren();
}

void UCUI_MAIN::AddUserBox(const FString& user)
{
	//유저를 유저목록에 추가
	if (nullptr != userBox)
	{
		if (false == userTable.Contains(user))
		{
			UCUI_USER* newUserUI = CreateWidget<UCUI_USER>(GetWorld(), UIUserClass.Get());
			if (nullptr != newUserUI)
			{
				newUserUI->uiMain = this;
				newUserUI->SetName(user);
				userTable.Emplace(user, newUserUI);
				userBox->AddChild(newUserUI);
			}
		}
	}
}

void UCUI_MAIN::RemoveUserBox(const FString& user)
{
	//유저를 유저목록에서 삭제
	if (nullptr != userBox)
	{
		if (true == userTable.Contains(user))
		{
			UCUI_USER* removeUser = nullptr;
			if (true == userTable.RemoveAndCopyValue(user, removeUser))
				userBox->RemoveChild(removeUser);
		}
	}
}

void UCUI_MAIN::RefreshUserBox(UPARAM(ref) const TArray<FString>& users)
{
	if (nullptr != userBox)
	{
		//유저 목록을 초기화 한 후
		userBox->ClearChildren();
		userTable.Reset();

		//입력값으로 유저목록 갱신
		for (const auto& user : users)
			AddUserBox(user);
	}
}