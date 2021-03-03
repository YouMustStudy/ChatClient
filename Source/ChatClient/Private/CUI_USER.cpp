// Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_USER.h"
#include "CUI_MAIN.h"
#include "..\Public\CUI_USER.h"

void UCUI_USER::SetName(const FString& name)
{
	//이름 설정
	if (nullptr != userName)
		userName->SetText(FText::FromString(name));
}

void UCUI_USER::SetMsgCommand()
{
	//메세지 입력창에 귓속말 생성
	if (nullptr != uiMain)
		uiMain->SetInputMsgBox("/msg " + userName->GetText().ToString() + " ");
}

void UCUI_USER::NativeConstruct()
{
	Super::NativeConstruct();
	if (nullptr != userMsgButton)
		userMsgButton->OnClicked.AddDynamic(this, &UCUI_USER::SetMsgCommand);
}
