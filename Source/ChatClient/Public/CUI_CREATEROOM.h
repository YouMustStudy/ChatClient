// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/SpinBox.h"
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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		USpinBox* roomNumberBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* roomNameInputBox;

	UPROPERTY(BlueprintReadWrite)
		AChatSocket* chatModule;

	UFUNCTION(BlueprintCallable)
		void ABCD();

	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//	class UTextBlock* ItemTitle = nullptr;

	virtual void NativeConstruct() override;
};
