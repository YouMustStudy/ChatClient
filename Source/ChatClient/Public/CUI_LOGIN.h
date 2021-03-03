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
	///< IP �Է¹ڽ�
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* inputIPBox;
	///< ID �Է¹ڽ�
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* inputIDBox;
	///< �α��� ��ư
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* loginButton;

	///< �Ŵ��� ��ü.
	UPROPERTY(BlueprintReadWrite)
	class AChatSocket* chatModule;
	/**
	*@brief �Է°����� ������ �α����Ѵ�.
	*/
	UFUNCTION(BlueprintCallable)
	void Login();
protected:
	virtual void NativeConstruct() override;
};
