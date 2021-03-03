// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "CUI_ERROR.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UCUI_ERROR : public UUserWidget
{
	GENERATED_BODY()
	
public:
	///< 에러가 출력될 텍스트창
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* errorMsg;

	///< 끄기 버튼
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* exitButton;

	/**
	*@brief 에러 메세지를 팝업창에 띄우는 함수.
	*param[in] errMsg 출력할 메세지
	*/
	UFUNCTION(BlueprintCallable)
	void PopupError(const FString& errMsg);

	/**
	*@brief 팝업창을 끄는 함수.
	*/
	UFUNCTION(BlueprintCallable)
	void PopdownError();

private:
	void NativeConstruct() override;
};
