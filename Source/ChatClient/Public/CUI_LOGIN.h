// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <regex>
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "CUI_LOGIN.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UCUI_LOGIN : public UUserWidget
{
	GENERATED_BODY()

public:
	///< IP 입력박스
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* inputIPBox;
	///< ID 입력박스
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* inputIDBox;
	///< 로그인 버튼
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* loginButton;

	///< 매니저 객체.
	UPROPERTY(BlueprintReadWrite)
	class AChatSocket* chatModule;
	/**
	*@brief 입력값으로 서버에 로그인한다.
	*/
	UFUNCTION(BlueprintCallable)
	void Login();
protected:
	virtual void NativeConstruct() override;
};
