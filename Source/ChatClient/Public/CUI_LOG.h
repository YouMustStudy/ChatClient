// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "CUI_LOG.generated.h"

/**
 *
 */
UCLASS()
class CHATCLIENT_API UCUI_LOG : public UUserWidget
{
	GENERATED_BODY()

public:
	//채팅 로그를 표현할 객체.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* chatLog;

protected:
	virtual void NativeConstruct() override;
};
