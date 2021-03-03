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
	///< ������ ��µ� �ؽ�Ʈâ
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* errorMsg;

	///< ���� ��ư
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* exitButton;

	/**
	*@brief ���� �޼����� �˾�â�� ���� �Լ�.
	*param[in] errMsg ����� �޼���
	*/
	UFUNCTION(BlueprintCallable)
	void PopupError(const FString& errMsg);

	/**
	*@brief �˾�â�� ���� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
	void PopdownError();

private:
	void NativeConstruct() override;
};
