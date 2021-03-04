// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Blueprint/UserWidget.h"
#include "CUI_ROOMLIST.generated.h"

class AChatModule;
/**
 *
 */
UCLASS()
class CHATCLIENT_API UCUI_ROOMLIST : public UUserWidget
{
	GENERATED_BODY()

public:
	///< 방를 표시할 UI 객체
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
		TAssetSubclassOf<class UCUI_ROOM> UIRoomClass;

	///< 돌아가기 버튼
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* returnButton;

	///< 새로고침 버튼
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* refreshButton;

	///< 방만들기 버튼
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* createButton;

	///< 방이 저장될 스크롤박스
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* roomList;

	///< 방만들기 UI 객체
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UCUI_CREATEROOM* uiCreateRoom;

	/**
	*@brief ROOMLIST UI와 CREATEROOM UI에 chatModule을 설정하는 함수.
	*@param[in] chatModule 저장할 chatModule 포인터.
	*/
	UFUNCTION(BlueprintCallable)
		void SetChatModule(AChatModule* newChatModule);

	/**
	*@brief 방목록 갱신을 요청하는 함수.
	*/
	UFUNCTION(BlueprintCallable)
		void RequestRefreshRoom();

	/**
	*@brief 방목록 갱신을 수행하는 함수
	*@param[in] rooms 방 이름들의 배열 객체.
	*/
	UFUNCTION(BlueprintCallable)
		void RefreshRoom(const TArray<FString>& rooms);

	/**
	*@brief 방 생성 UI를 띄우는 함수.
	*/
	UFUNCTION(BlueprintCallable)
		void PopupCreateUI();

	/**
	*@brief 다시 메인로비로 돌아가는 함수
	*/
	UFUNCTION(BlueprintCallable)
		void ChangeToMain();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	///< 매니저 모듈.
	AChatModule* chatModule;

	void NativeConstruct() override;
};
