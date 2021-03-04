// Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_CREATEROOM.h"
#include "ChatModule.h"

void UCUI_CREATEROOM::RequestCreateRoom()
{
	if (nullptr != roomNameInputBox)
	{
		//�� �̸��� �����̸� ��ó��.
		FText roomName = roomNameInputBox->GetText();
		if (true == roomName.IsEmpty())
		{
			return;
		}
		if (nullptr != roomNumberBox)
		{
			//���� Ŀ�ǵ带 �����Ͽ� �����Ѵ�.
			int32 userNum = static_cast<int32>(roomNumberBox->GetValue());
			FString CreateRoomCommand = FString(L"/create ") + roomName.ToString() + " " + FString::FromInt(userNum);
			if (nullptr != chatModule)
				chatModule->SendMsg(CreateRoomCommand);
			roomNameInputBox->SetText(FText::GetEmpty());
			HideCreateUI();
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

void UCUI_CREATEROOM::LimitTextLengthOnTextChanged(const FText& InText)
{
	//�ؽ�Ʈ ���̰� MAX_LENGTH���� �Ѿ�� ��.
	static const int MAX_LENGTH = 20;
	FString textMsg = InText.ToString();
	if (MAX_LENGTH < textMsg.Len())
	{
		textMsg.RemoveAt(textMsg.Len() - 1);
		if (nullptr != roomNameInputBox)
			roomNameInputBox->SetText(FText::FromString(textMsg));
	}
}

void UCUI_CREATEROOM::NativeConstruct()
{
	Super::NativeConstruct();
	if (nullptr != enterButton)
		enterButton->OnClicked.AddDynamic(this, &UCUI_CREATEROOM::RequestCreateRoom);
	if (nullptr != returnButton)
		returnButton->OnClicked.AddDynamic(this, &UCUI_CREATEROOM::HideCreateUI);
	if (nullptr != roomNameInputBox)
		roomNameInputBox->OnTextChanged.AddDynamic(this, &UCUI_CREATEROOM::LimitTextLengthOnTextChanged);
}