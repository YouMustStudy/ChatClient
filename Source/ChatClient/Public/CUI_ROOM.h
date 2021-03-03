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
	///< 방제목을 나타내는 텍스트.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* roomText;

	///< 방 이름 클릭 시 해당 방으로 넘어가는 버튼.
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* joinButton;

	///< 메인 매니저 객체.
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class AChatSocket* chatModule;

	/**
	*@brief 방에 입장하는 커맨드를 송신하는 함수.
	*/
	UFUNCTION(BlueprintCallable)
	void JoinRoom();

	/**
	*@brief 방의 이름을 설정하는 함수.
	*/
	UFUNCTION(BlueprintCallable)
	void SetName(const FString& name);

	virtual void NativeConstruct() override;
};
