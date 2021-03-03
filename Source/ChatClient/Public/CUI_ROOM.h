// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include <regex>
#include "CUI_ROOM.generated.h"

/**
 * 
 */
UCLASS()
class CHATCLIENT_API UCUI_ROOM : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* roomText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* joinButton;

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class AChatSocket* chatModule;

	UFUNCTION(BlueprintCallable)
	void JoinRoom();

	virtual void NativeConstruct() override;
};
