// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "CUI_MAIN.generated.h"

constexpr int32 MAX_CHAT_LOG = 100;
/**
 * 
 */
UCLASS()
class CHATCLIENT_API UCUI_MAIN : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
	TAssetSubclassOf<class UCUI_LOG> UILogClass;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* chatBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* userBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* roomNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UEditableTextBox* inputMsgBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* sendButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* roomButton;

	UPROPERTY(BlueprintReadWrite)
	class AChatSocket* chatModule;

	UFUNCTION(BlueprintCallable)
	void AddChatLog(FString& msg);

	UFUNCTION(BlueprintCallable)
	void AddUserList(FString& user);

	UFUNCTION(BlueprintCallable)
	void RemoveUserList(FString& user);

	UFUNCTION(BlueprintCallable)
	void Refresh(TArray<FString> &user);

	virtual void NativeConstruct() override;

private:

};
