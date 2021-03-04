// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "CUI_MAIN.generated.h"


/**
 *
 */
constexpr int32 MAX_CHAT_LOG = 100;
UCLASS()
class CHATCLIENT_API UCUI_MAIN : public UUserWidget
{
	GENERATED_BODY()
	
public:
	///< ä�� �α׸� ǥ���� UI ��ü
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
		TAssetSubclassOf<class UCUI_LOG> UILogClass;

	///< �����ڸ� ǥ���� UI ��ü
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
		TAssetSubclassOf<class UCUI_USER> UIUserClass;

	///< ä�÷αװ� ǥ�õǴ� ScrollBox
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* chatBox;

	///< ������ �������� ǥ�õǴ� ScrollBox
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* userBox;

	///< ������ �� �̸��� ǥ�õǴ� TextBlock
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* roomNameText;

	///< �޼����� �Է��� �Է¹ڽ�
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* inputMsgBox;

	///< ������ ��ư
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* sendButton;

	///< �� ��� ��ư
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* roomButton;

	///< ���� ���
	UPROPERTY(BlueprintReadWrite)
		class AChatModule* chatModule;

	/**
	*@brief �������� �����ϴ� �Լ�.
	*@param[in] name ������ �� �̸�.
	*/
	UFUNCTION(BlueprintCallable)
		void SetRoomName(const FString& name);

	/**
	*@brief �������� �����ϴ� �Լ�.
	*@param[in] name ������ �� �̸�.
	*/
	UFUNCTION(BlueprintCallable)
		void ClearInputMsgBox();

	/**
	*@brief �Է°��� ������� ä���� �����ϴ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
		void SendChat();

	/**
	*@brief ä�� �Է�â�� Ư�� ���ڿ��� �����ϴ� �Լ�.
	*@param[in] msg ������ ���ڿ�.
	*/
	UFUNCTION(BlueprintCallable)
		void SetInputMsgBox(const FString& msg);

	/**
	*@brief ���ڿ��� ä��â�� �߰��ϴ� �Լ�.
	*@param[in] msg �߰��� ���ڿ�.
	*/
	UFUNCTION(BlueprintCallable)
		void AddChatLog(UPARAM(ref) const FString& msg, FLinearColor color = FLinearColor(0, 0, 0, 1.0));

	/**
	*@brief ä��â�� �ʱ�ȭ�ϴ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
		void ClearChatLog();

	/**
	*@brief ������ ������ ���� ��Ͽ� ����ϴ� �Լ�
	*@param[in] user ���� ������ �̸� ���ڿ�
	*/
	UFUNCTION(BlueprintCallable)
		void AddUserBox(const FString& user);

	/**
	*@brief ������ ������ ���� ��Ͽ��� �����ϴ� �Լ�
	*@param[in] user ���� ������ �̸� ���ڿ�
	*/
	UFUNCTION(BlueprintCallable)
		void RemoveUserBox(const FString& user);

	/**
	*@brief ���� ����� ���� �ʱ�ȭ�ϴ� �Լ�.
	*@param[in] users �ʱ�ȭ �� �� �߰��� �������� �̸� �迭
	*/
	UFUNCTION(BlueprintCallable)
		void RefreshUserBox(UPARAM(ref) const TArray<FString>& users);

	/**
	*@brief ���� ����� ��û�ϴ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
		void RequestRoomList();

	/**
	*@brief �޼��� �Է�â���� ���� �� ȣ��Ǵ� �Լ�.
	*/
	UFUNCTION(BlueprintCallable)
		void InputMsgBoxOnTextCommitted(const FText& InText, ETextCommit::Type InCommitType);

private:
	virtual void NativeConstruct() override;

	///< ��������� �����ϴ� ���̺�.
	TMap<FString, UCUI_USER*> userTable;
};
