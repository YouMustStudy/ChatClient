// Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_ERROR.h"

void UCUI_ERROR::PopupError(const FString& errMsg)
{
	//�޼��� ���� �� �˾�
	if (nullptr != errorMsg)
	{
		errorMsg->SetText(FText::FromString(errMsg));
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UCUI_ERROR::PopdownError()
{
	//�˾� ����
	SetVisibility(ESlateVisibility::Collapsed);
}

void UCUI_ERROR::NativeConstruct()
{
	Super::NativeConstruct();
	if (nullptr != exitButton)
		exitButton->OnClicked.AddDynamic(this, &UCUI_ERROR::PopdownError);
	SetVisibility(ESlateVisibility::Collapsed);
}

