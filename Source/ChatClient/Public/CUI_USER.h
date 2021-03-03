// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "CUI_USER.generated.h"

/**
 *
 */
UCLASS()
class CHATCLIENT_API UCUI_USER : public UUserWidget
{
	GENERATED_BODY()

public:
	///>유저 이름을 나타내는 객체
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* userName;
	///>유저 귓속말을 위한 버튼
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* userMsgButton;
	
	/**
	*@brief 유저 이름을 설정하는 함수.
	*@param[in] name 설정할 문자열
	*/
	UFUNCTION(BlueprintCallable)
		void SetName(const FString& name);

	/**
	*@brief 채팅 입력박스에 귓속말 커맨드 생성
	*/
	UFUNCTION(BlueprintCallable)
		void SetMsgCommand();

	///>메인화면 UI
	UPROPERTY(BlueprintReadWrite)
		class UCUI_MAIN* uiMain;

protected:
	virtual void NativeConstruct() override;
};
