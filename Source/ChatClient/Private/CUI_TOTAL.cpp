// Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_TOTAL.h"
#include "ChatModule.h"

void UCUI_TOTAL::InitUI(AChatModule* cModule)
{
	//최초 로그인 화면으로 이동 및 모듈 설정.
	chatModule = cModule;
	if (nullptr != uiLogin)
		uiLogin->chatModule = cModule;
	if (nullptr != uiMain)
		uiMain->chatModule = cModule;
	if (nullptr != uiRoomList)
		uiRoomList->SetChatModule(cModule);
	ChangeSceneTo(SC_TYPE::LOGIN);
}

void UCUI_TOTAL::ChangeSceneTo(SC_TYPE sc_type)
{
	//포인터를 비교해서 해당씬과 다르면 숨기기, 맞으면 활성화.
	switch (sc_type)
	{
	case SC_TYPE::LOGIN:
		uiLogin->SetVisibility(ESlateVisibility::Visible);
		uiMain->SetVisibility(ESlateVisibility::Collapsed);
		uiRoomList->SetVisibility(ESlateVisibility::Collapsed);
		break;

	case SC_TYPE::MAIN:
		uiLogin->SetVisibility(ESlateVisibility::Collapsed);
		uiMain->SetVisibility(ESlateVisibility::Visible);
		uiRoomList->SetVisibility(ESlateVisibility::Collapsed);
		break;

	case SC_TYPE::ROOMLIST:
		uiLogin->SetVisibility(ESlateVisibility::Collapsed);
		uiMain->SetVisibility(ESlateVisibility::Collapsed);
		uiRoomList->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

void UCUI_TOTAL::PopError(const FString& msg)
{
	//에러 팝업
	if (nullptr != uiError)
		uiError->PopupError(msg);
}

void UCUI_TOTAL::EnterRoom(const FString& name)
{
	//채팅창 초기화 후 새 방 입장
	if (nullptr != uiMain)
	{
		uiMain->ClearChatLog();
		uiMain->ClearInputMsgBox();
		uiMain->SetRoomName(name);
		ChangeSceneTo(SC_TYPE::MAIN);
	}
}

void UCUI_TOTAL::EnterRoomList(const TArray<FString>& rooms)
{
	//방목록 초기화
	if (nullptr != uiRoomList)
	{
		uiRoomList->RefreshRoom(rooms);
		ChangeSceneTo(SC_TYPE::ROOMLIST);
	}
}

void UCUI_TOTAL::RefreshUserBox(const TArray<FString>& users)
{
	//유저목록 갱신
	if (nullptr != uiMain)
	{
		uiMain->RefreshUserBox(users);
	}
}

void UCUI_TOTAL::AddUserBox(const FString& user)
{
	//유저목록에 유저 추가
	if (nullptr != uiMain)
	{
		uiMain->AddUserBox(user);
	}
}

void UCUI_TOTAL::RemoveUserBox(const FString& user)
{
	//유저목록에 유저 삭제
	if (nullptr != uiMain)
	{
		uiMain->RemoveUserBox(user);
	}
}

void UCUI_TOTAL::AddChatLog(const TArray<FString>& msgs, FLinearColor color)
{
	//채팅창에 채팅로그 추가
	if (nullptr != uiMain)
	{
		for (const auto& msg : msgs)
			uiMain->AddChatLog(msg, color);
	}
}

void UCUI_TOTAL::NativeConstruct()
{
	Super::NativeConstruct();
}

