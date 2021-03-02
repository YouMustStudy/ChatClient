// Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_CREATEROOM.h"

void UCUI_CREATEROOM::ABCD()
{
	FText roomName = roomNameInputBox->GetText();
	if (true == roomName.IsEmpty())
		return;

	int32 userNum = static_cast<int32>(roomNumberBox->GetValue());
	FString CreateRoomCommand = FString(L"/create ") + roomName.ToString() + " " + FString::FromInt(userNum);
	chatModule->SendMsg(CreateRoomCommand);
}

void UCUI_CREATEROOM::NativeConstruct()
{
	Super::NativeConstruct();
}