// Fill out your copyright notice in the Description page of Project Settings.

#include "CUI_ROOMLIST.h"
#include "CUI_ROOM.h"
#include "CUI_CREATEROOM.h"
#include "ChatModule.h"

void UCUI_ROOMLIST::SetChatModule(AChatModule* newChatModule)
{
	//���ϰ� �����â�� �Ŵ��� ��� �Ҵ�.
	this->chatModule = newChatModule;
	if (nullptr != uiCreateRoom)
		uiCreateRoom->chatModule = newChatModule;
}

void UCUI_ROOMLIST::RequestRefreshRoom()
{
	//�� ���ΰ�ħ ��û.
	static FString refreshCommand{ "/roomlist" };
	if(nullptr != chatModule)
		chatModule->SendMsg(refreshCommand);
}

void UCUI_ROOMLIST::RefreshRoom(const TArray<FString>& rooms)
{
	if (nullptr != roomList)
	{
		//������ �� ��ϵ��� �ʱ�ȭ�ϰ�
		roomList->ClearChildren();
		for (auto& room : rooms)
		{
			//�Է°��� ������� �� ����� �����Ѵ�.
			UCUI_ROOM* newRoomEntity = CreateWidget<UCUI_ROOM>(GetWorld(), UIRoomClass.Get());
			if (nullptr != newRoomEntity)
			{
				newRoomEntity->SetName(room);
				newRoomEntity->chatModule = chatModule;
				roomList->AddChild(newRoomEntity);
			}
		}
	}
}

void UCUI_ROOMLIST::PopupCreateUI()
{
	//�� ����â�� ����
	if (nullptr != uiCreateRoom)
		uiCreateRoom->Popup();
}

void UCUI_ROOMLIST::ChangeToMain()
{
	//����ȭ������ ��ȯ
	if (nullptr != chatModule)
		if (nullptr != chatModule->uiTotal)
			chatModule->uiTotal->ChangeSceneTo(SC_TYPE::MAIN);
}

void UCUI_ROOMLIST::NativeConstruct()
{
	Super::NativeConstruct();
	//��ư�� �Լ� �Ҵ�.
	if (nullptr != createButton)
		createButton->OnClicked.AddDynamic(this, &UCUI_ROOMLIST::PopupCreateUI);
	if(nullptr != refreshButton)
		refreshButton->OnClicked.AddDynamic(this, &UCUI_ROOMLIST::RequestRefreshRoom);
	if (nullptr != returnButton)
		returnButton->OnClicked.AddDynamic(this, &UCUI_ROOMLIST::ChangeToMain);
	if (nullptr != uiCreateRoom)
		uiCreateRoom->SetVisibility(ESlateVisibility::Collapsed);
}