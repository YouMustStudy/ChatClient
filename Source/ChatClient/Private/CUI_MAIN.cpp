// Fill out your copyright notice in the Description page of Project Settings.
#include "CUI_MAIN.h"
#include "CUI_LOG.h"

void UCUI_MAIN::AddChatLog(FString& msg)
{

	int32 chatLogCnt = chatBox->GetChildrenCount();
	if (chatLogCnt >= MAX_CHAT_LOG)
		chatBox->RemoveChildAt(0);

	UCUI_LOG* UILog = CreateWidget<UCUI_LOG>(GetWorld(), UILogClass.Get());
	if (nullptr != UILog)
	{
		UILog->chatLog->SetText(FText::FromString(msg));
		chatBox->AddChild(UILog);
	}
}

void UCUI_MAIN::AddUserList(FString& user)
{
}

void UCUI_MAIN::RemoveUserList(FString& user)
{
}

void UCUI_MAIN::Refresh(TArray<FString>& user)
{
}

void UCUI_MAIN::NativeConstruct()
{
	Super::NativeConstruct();
}
