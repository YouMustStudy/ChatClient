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
	///< �渦 ǥ���� UI ��ü
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
		TAssetSubclassOf<class UCUI_ROOM> UIRoomClass;

	///< ���ư��� ��ư
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* returnButton;

	///< ���ΰ�ħ ��ư
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* refreshButton;

	///< �游��� ��ư
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* createButton;

	///< ���� ����� ��ũ�ѹڽ�
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* roomList;

	///< �游��� UI ��ü
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UCUI_CREATEROOM* uiCreateRoom;

	/**
	*@brief ROOMLIST UI�� CREATEROOM UI�� chatModule�� �����ϴ� �Լ�.
	*@param[in] chatModule ������ chatModule ������.
	*/
	UFUNCTION(BlueprintCallable)
		void SetChatModule(AChatModule* newChatModule);

	/**
	*@brief ���� ������ ��û�ϴ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
		void RequestRefreshRoom();

	/**
	*@brief ���� ������ �����ϴ� �Լ�
	*@param[in] rooms �� �̸����� �迭 ��ü.
	*/
	UFUNCTION(BlueprintCallable)
		void RefreshRoom(const TArray<FString>& rooms);

	/**
	*@brief �� ���� UI�� ���� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
		void PopupCreateUI();

	/**
	*@brief �ٽ� ���ηκ�� ���ư��� �Լ�
	*/
	UFUNCTION(BlueprintCallable)
		void ChangeToMain();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	///< �Ŵ��� ���.
	AChatModule* chatModule;

	void NativeConstruct() override;
};
