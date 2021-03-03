 //Fill out your copyright notice in the Description page of Project Settings.


#include "CUI_ROOM.h"
#include "ChatModule.h"

void UCUI_ROOM::NativeConstruct()
{
	Super::NativeConstruct();
	//���� ��ư�� �Լ� �Ҵ�.
	if(nullptr != joinButton)
		joinButton->OnClicked.AddDynamic(this, &UCUI_ROOM::JoinRoom);
}

void UCUI_ROOM::JoinRoom()
{
	//�� �̸� �պκп��� �ε��� ���� �� ���� Ŀ�ǵ� ����.
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
	//�̸� ����
	if (nullptr != roomText)
		roomText->SetText(FText::FromString(name));
}