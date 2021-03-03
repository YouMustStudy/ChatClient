// Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_CREATEROOM.h"
#include "ChatSocket.h"

void UCUI_CREATEROOM::RequestCreateRoom()
{
	if (nullptr != roomNameInputBox)
	{
		//�� �̸��� �����̸� ��ó��.
		FText roomName = roomNameInputBox->GetText();
		if (true == roomName.IsEmpty())
			return;

		if (nullptr != roomNumberBox)
		{
			//���� Ŀ�ǵ带 �����Ͽ� �����Ѵ�.
			int32 userNum = static_cast<int32>(roomNumberBox->GetValue());
			FString CreateRoomCommand = FString(L"/create ") + roomName.ToString() + " " + FString::FromInt(userNum);
			if(nullptr != chatModule)
				chatModule->SendMsg(CreateRoomCommand);
			roomNameInputBox->SetText(FText::GetEmpty());
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UCUI_CREATEROOM::HideCreateUI()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UCUI_CREATEROOM::NativeConstruct()
{
	Super::NativeConstruct();
	if (nullptr != enterButton)
		enterButton->OnClicked.AddDynamic(this, &UCUI_CREATEROOM::RequestCreateRoom);
	if(nullptr != returnButton)
		returnButton->OnClicked.AddDynamic(this, &UCUI_CREATEROOM::HideCreateUI);
}