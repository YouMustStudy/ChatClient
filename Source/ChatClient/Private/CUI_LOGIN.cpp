// Fill out your copyright notice in the Description page of Project Settings.
#include "CUI_LOGIN.h"
#include "ChatSocket.h"

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
		if (true == chatModule->ConnectServer(FString(wideMatch[1].str().c_str()), stoi(wideMatch[6].str())))
		{
			FString ID = inputIDBox->GetText().ToString();
			if (false == ID.IsEmpty())
				chatModule->SendMsg(loginPrefix + ID);
		}
	}
}

void UCUI_LOGIN::NativeConstruct()
{
	Super::NativeConstruct();
	if (nullptr != loginButton)
		loginButton->OnClicked.AddDynamic(this, &UCUI_LOGIN::Login);
}