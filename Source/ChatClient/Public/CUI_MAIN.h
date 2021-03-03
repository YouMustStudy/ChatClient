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
	/// 채팅 로그를 표시할 UI 객체
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
	TAssetSubclassOf<class UCUI_LOG> UILogClass;

	/// 접속자를 표시할 UI 객체
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
	TAssetSubclassOf<class UCUI_USER> UIUserClass;

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
	void SendChat();

	UFUNCTION(BlueprintCallable)
	void SetInputMsgBox(const FString& msg);

	UFUNCTION(BlueprintCallable)
	void AddChatLog(UPARAM(ref) const FString& msg);

	UFUNCTION(BlueprintCallable)
	void ClearChatLog();

	UFUNCTION(BlueprintCallable)
	void AddUserBox(const FString& user);

	UFUNCTION(BlueprintCallable)
	void RemoveUserBox(const FString& user);

	UFUNCTION(BlueprintCallable)
	void RefreshUserBox(UPARAM(ref) const TArray<FString>& users);

	UFUNCTION(BlueprintCallable)
	void RequestRoomList();

private:
	virtual void NativeConstruct() override;

	TMap<FString, UCUI_USER*> userTable;
};
