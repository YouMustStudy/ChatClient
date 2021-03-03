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
	///< �������� ��Ÿ���� �ؽ�Ʈ.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* roomText;

	///< �� �̸� Ŭ�� �� �ش� ������ �Ѿ�� ��ư.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* joinButton;

	///< ���� �Ŵ��� ��ü.
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class AChatSocket* chatModule;

	/**
	*@brief �濡 �����ϴ� Ŀ�ǵ带 �۽��ϴ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
	void JoinRoom();

	/**
	*@brief ���� �̸��� �����ϴ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
	void SetName(const FString& name);

	virtual void NativeConstruct() override;
};
