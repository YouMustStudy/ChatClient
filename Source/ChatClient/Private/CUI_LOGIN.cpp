// Fill out your copyright notice in the Description page of Project Settings.
#include "CUI_LOGIN.h"
#include "ChatModule.h"

void UCUI_LOGIN::Login()
{
	static FString loginPrefix = "/login ";
	if (nullptr == inputIPBox ||
		nullptr == inputIDBox ||
		nullptr == chatModule)
		return;

	//정규식으로 IP, PORT 파싱
	FString ipAddr = inputIPBox->GetText().ToString();
	std::wregex ipParser(LR"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)):([0-9]{1,5})$)");
	std::wcmatch wideMatch;
	if (true == std::regex_match(*ipAddr, wideMatch, ipParser))
	{
		FString ID = inputIDBox->GetText().ToString();
		if (false == ID.IsEmpty())
		{
			if (true == chatModule->ConnectServer(FString(wideMatch[1].str().c_str()), stoi(wideMatch[6].str())))
			{
				chatModule->SendMsg(loginPrefix + ID);
			}
		}
	}
}

void UCUI_LOGIN::NativeConstruct()
{
	Super::NativeConstruct();
	if (nullptr != loginButton)
		loginButton->OnClicked.AddDynamic(this, &UCUI_LOGIN::Login);
	if (nullptr != inputIDBox)
		inputIDBox->OnTextChanged.AddDynamic(this, &UCUI_LOGIN::LimitTextLengthInputIDBoxOnTextChanged);
	if (nullptr != inputIPBox)
		inputIPBox->OnTextChanged.AddDynamic(this, &UCUI_LOGIN::LimitTextLengthInputIPBoxOnTextChanged);
}

void UCUI_LOGIN::LimitTextLengthInputIDBoxOnTextChanged(const FText& InText)
{
	//텍스트 길이가 MAX_LENGTH값을 넘어가면 컷.
	static const int MAX_LENGTH = 20;
	FString textMsg = InText.ToString();
	if (MAX_LENGTH < textMsg.Len())
	{
		textMsg.RemoveAt(textMsg.Len() - 1);
		if (nullptr != inputIDBox)
			inputIDBox->SetText(FText::FromString(textMsg));
	}
}

void UCUI_LOGIN::LimitTextLengthInputIPBoxOnTextChanged(const FText& InText)
{
	//텍스트 길이가 MAX_LENGTH값을 넘어가면 컷.
	static const int MAX_LENGTH = 30;
	FString textMsg = InText.ToString();
	if (MAX_LENGTH < textMsg.Len())
	{
		textMsg.RemoveAt(textMsg.Len() - 1);
		if (nullptr != inputIPBox)
			inputIPBox->SetText(FText::FromString(textMsg));
	}
}