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
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* userName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* userMsgButton;

	UFUNCTION(BlueprintCallable)
	void SetName(const FString& name);

	UFUNCTION(BlueprintCallable)
	void SetMsgCommand();

	UPROPERTY(BlueprintReadWrite)
	class UCUI_MAIN* uiMain;

protected:
	virtual void NativeConstruct() override;
};
