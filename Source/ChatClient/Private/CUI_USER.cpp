// Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_USER.h"
#include "CUI_MAIN.h"
#include "..\Public\CUI_USER.h"

void UCUI_USER::SetName(const FString& name)
{
	if (nullptr != userName)
		userName->SetText(FText::FromString(name));
}

void UCUI_USER::SetMsgCommand()
{
	if (nullptr != uiMain)
		uiMain->SetInputMsgBox("/msg " + userName->GetText().ToString() + " ");
}

void UCUI_USER::NativeConstruct()
{
	Super::NativeConstruct();
	if (nullptr != userMsgButton)
		userMsgButton->OnClicked.AddDynamic(this, &UCUI_USER::SetMsgCommand);
}
