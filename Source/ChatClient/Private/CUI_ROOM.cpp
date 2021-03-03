 //Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_ROOM.h"
#include "ChatSocket.h"

void UCUI_ROOM::NativeConstruct()
{
	Super::NativeConstruct();
	joinButton->OnClicked.AddDynamic(this, &UCUI_ROOM::JoinRoom);
}

void UCUI_ROOM::JoinRoom()
{
	FString roomName = roomText->GetText().ToString();
	std::wregex indexParser(LR"(^\[([0-9]+)\].+)");
	std::wcmatch wideMatch;

	if (true == std::regex_match(*roomName, wideMatch, indexParser))
	{
		if (nullptr != chatModule) 
		{
			FString CreateRoomCommand = L"/join " + FString(wideMatch[1].str().c_str());
			chatModule->SendMsg(CreateRoomCommand);
		}
	}
}