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
	///< ���� �ִ��ο����� �����ϴ� SpinBox
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USpinBox* roomNumberBox;

	///< ���� �̸��� �Է¹޴� EditableTextBox
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* roomNameInputBox;

	///< Ȯ�� ��ư.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* enterButton;

	///< �ٽ� �� ������� ���ư��� ��ư.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* returnButton;

	/**
	*@brief �Էµ� ���� ������� �� ������ ��û�ϴ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
		void RequestCreateRoom();

	/**
	*@brief �ٽ� �� ������� ���ư��� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
	void HideCreateUI();

	virtual void NativeConstruct() override;
public:
	///< �Ŵ��� ��ü.
	UPROPERTY(BlueprintReadWrite)
		AChatSocket* chatModule;
};
