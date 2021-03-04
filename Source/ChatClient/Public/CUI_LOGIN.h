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
		class AChatModule* chatModule;

	/**
	*@brief �Է°����� ������ �α����Ѵ�.
	*/
	UFUNCTION(BlueprintCallable)
		void Login();

	/**
	*@brief ���̵� �Է¹ڽ��� �Է¼��� �����ϴ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
	void LimitTextLengthInputIDBoxOnTextChanged(const FText& InText);

	/**
	*@brief IP �Է¹ڽ��� �Է¼��� �����ϴ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
	void LimitTextLengthInputIPBoxOnTextChanged(const FText& InText);

protected:
	virtual void NativeConstruct() override;


};
