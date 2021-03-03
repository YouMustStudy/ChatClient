 //Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_ROOM.h"
#include "ChatModule.h"

void UCUI_ROOM::NativeConstruct()
{
	Super::NativeConstruct();
	//입장 버튼에 함수 할당.
	if(nullptr != joinButton)
		joinButton->OnClicked.AddDynamic(this, &UCUI_ROOM::JoinRoom);
}

void UCUI_ROOM::JoinRoom()
{
	//방 이름 앞부분에서 인덱스 추출 후 입장 커맨드 전송.
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

void UCUI_ROOM::SetName(const FString& name)
{
	//이름 설정
	if (nullptr != roomText)
		roomText->SetText(FText::FromString(name));
}