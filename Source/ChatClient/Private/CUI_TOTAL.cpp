// Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_TOTAL.h"
#include "ChatModule.h"

void UCUI_TOTAL::InitUI(AChatModule* cModule)
{
	//���� �α��� ȭ������ �̵� �� ��� ����.
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
	//�����͸� ���ؼ� �ش���� �ٸ��� �����, ������ Ȱ��ȭ.
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
	//���� �˾�
	if (nullptr != uiError)
		uiError->PopupError(msg);
}

void UCUI_TOTAL::EnterRoom(const FString& name)
{
	//ä��â �ʱ�ȭ �� �� �� ����
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
	//���� �ʱ�ȭ
	if (nullptr != uiRoomList)
	{
		uiRoomList->RefreshRoom(rooms);
		ChangeSceneTo(SC_TYPE::ROOMLIST);
	}
}

void UCUI_TOTAL::RefreshUserBox(const TArray<FString>& users)
{
	//������� ����
	if (nullptr != uiMain)
	{
		uiMain->RefreshUserBox(users);
	}
}

void UCUI_TOTAL::AddUserBox(const FString& user)
{
	//������Ͽ� ���� �߰�
	if (nullptr != uiMain)
	{
		uiMain->AddUserBox(user);
	}
}

void UCUI_TOTAL::RemoveUserBox(const FString& user)
{
	//������Ͽ� ���� ����
	if (nullptr != uiMain)
	{
		uiMain->RemoveUserBox(user);
	}
}

void UCUI_TOTAL::AddChatLog(const TArray<FString>& msgs, FLinearColor color)
{
	//ä��â�� ä�÷α� �߰�
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

