// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/SpinBox.h"
#include "Components/Button.h"
#include "ChatSocket.h"
#include "CUI_CREATEROOM.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UCUI_CREATEROOM : public UUserWidget
{
	GENERATED_BODY()

protected:
	///< 방의 최대인원수를 결정하는 SpinBox
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USpinBox* roomNumberBox;

	///< 방의 이름을 입력받는 EditableTextBox
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* roomNameInputBox;

	///< 확인 버튼.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* enterButton;

	///< 다시 방 목록으로 돌아가는 버튼.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* returnButton;

	/**
	*@brief 입력된 값을 기반으로 방 생성을 요청하는 함수.
	*/
	UFUNCTION(BlueprintCallable)
		void RequestCreateRoom();

	/**
	*@brief 다시 방 목록으로 돌아가는 함수.
	*/
	UFUNCTION(BlueprintCallable)
	void HideCreateUI();

	virtual void NativeConstruct() override;
public:
	///< 매니저 객체.
	UPROPERTY(BlueprintReadWrite)
		AChatSocket* chatModule;
};
