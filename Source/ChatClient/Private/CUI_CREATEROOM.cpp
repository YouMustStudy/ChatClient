// Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_CREATEROOM.h"
#include "ChatModule.h"

void UCUI_CREATEROOM::RequestCreateRoom()
{
	if (nullptr != roomNameInputBox)
	{
		//방 이름이 공백이면 미처리.
		FText roomName = roomNameInputBox->GetText();
		if (true == roomName.IsEmpty())
		{
			return;
		}
		if (nullptr != roomNumberBox)
		{
			//이후 커맨드를 조합하여 전송한다.
			int32 userNum = static_cast<int32>(roomNumberBox->GetValue());
			FString CreateRoomCommand = FString(L"/create ") + roomName.ToString() + " " + FString::FromInt(userNum);
			if (nullptr != chatModule)
				chatModule->SendMsg(CreateRoomCommand);
			roomNameInputBox->SetText(FText::GetEmpty());
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UCUI_CREATEROOM::Popup()
{
	if (false == isPop)
	{
		if (nullptr != roomNameInputBox)
			roomNameInputBox->SetText(FText::GetEmpty());
		if (nullptr != roomNumberBox)
		{
			roomNumberBox->SetValue(roomNumberBox->GetMinValue());
		}
		SetVisibility(ESlateVisibility::Visible);
		isPop = true;
	}
}

void UCUI_CREATEROOM::HideCreateUI()
{
	if (true == isPop)
	{
		SetVisibility(ESlateVisibility::Collapsed);
		isPop = false;
	}
}

void UCUI_CREATEROOM::NativeConstruct()
{
	Super::NativeConstruct();
	if (nullptr != enterButton)
		enterButton->OnClicked.AddDynamic(this, &UCUI_CREATEROOM::RequestCreateRoom);
	if (nullptr != returnButton)
		returnButton->OnClicked.AddDynamic(this, &UCUI_CREATEROOM::HideCreateUI);
}