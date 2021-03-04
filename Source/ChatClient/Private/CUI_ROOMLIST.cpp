// Fill out your copyright notice in the Description page of Project Settings.

#include "CUI_ROOMLIST.h"
#include "CUI_ROOM.h"
#include "CUI_CREATEROOM.h"
#include "ChatModule.h"

void UCUI_ROOMLIST::SetChatModule(AChatModule* newChatModule)
{
	//방목록과 방생성창의 매니저 모듈 할당.
	this->chatModule = newChatModule;
	if (nullptr != uiCreateRoom)
		uiCreateRoom->chatModule = newChatModule;
}

void UCUI_ROOMLIST::RequestRefreshRoom()
{
	//방 새로고침 요청.
	static FString refreshCommand{ "/roomlist" };
	if(nullptr != chatModule)
		chatModule->SendMsg(refreshCommand);
}

void UCUI_ROOMLIST::RefreshRoom(const TArray<FString>& rooms)
{
	if (nullptr != roomList)
	{
		//생성된 룸 목록들을 초기화하고
		roomList->ClearChildren();
		for (auto& room : rooms)
		{
			//입력값을 기반으로 새 방들을 생성한다.
			if (nullptr != RoomUIClass)
			{
				UCUI_ROOM* newRoomEntity = CreateWidget<UCUI_ROOM>(GetWorld(), RoomUIClass);
				if (nullptr != newRoomEntity)
				{
					newRoomEntity->SetName(room);
					newRoomEntity->chatModule = chatModule;
					roomList->AddChild(newRoomEntity);
				}
			}
		}
	}
}

void UCUI_ROOMLIST::PopupCreateUI()
{
	//방 생성창을 종료
	if (nullptr != uiCreateRoom)
		uiCreateRoom->Popup();
}

void UCUI_ROOMLIST::ChangeToMain()
{
	//메인화면으로 전환
	if (nullptr != chatModule)
		if (nullptr != chatModule->uiTotal)
			chatModule->uiTotal->ChangeSceneTo(SC_TYPE::MAIN);
}

void UCUI_ROOMLIST::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	static float tickTime = 0;
	constexpr float refreshTime = 3.0; //3sec.

	tickTime += InDeltaTime;
	if (refreshTime <= tickTime)
	{
		tickTime -= refreshTime;
		RequestRefreshRoom();
	}
}

void UCUI_ROOMLIST::NativeConstruct()
{
	Super::NativeConstruct();
	RoomUIClass = ConstructorHelpersInternal::FindOrLoadClass(RoomUIPath, UUserWidget::StaticClass());

	//버튼에 함수 할당.
	if (nullptr != createButton)
		createButton->OnClicked.AddDynamic(this, &UCUI_ROOMLIST::PopupCreateUI);
	if(nullptr != refreshButton)
		refreshButton->OnClicked.AddDynamic(this, &UCUI_ROOMLIST::RequestRefreshRoom);
	if (nullptr != returnButton)
		returnButton->OnClicked.AddDynamic(this, &UCUI_ROOMLIST::ChangeToMain);
	if (nullptr != uiCreateRoom)
		uiCreateRoom->SetVisibility(ESlateVisibility::Collapsed);
}