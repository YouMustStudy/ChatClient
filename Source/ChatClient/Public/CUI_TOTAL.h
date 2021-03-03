// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CUI_LOGIN.h"
#include "CUI_MAIN.h"
#include "CUI_ROOMLIST.h"
#include "CUI_ERROR.h"
#include "CUI_TOTAL.generated.h"

UENUM()
enum class SC_TYPE : uint8
{
	LOGIN,
	MAIN,
	ROOMLIST
};
/**
 * 
 */
UCLASS()
class CHATCLIENT_API UCUI_TOTAL : public UUserWidget
{
	GENERATED_BODY()
	
public:
	///< �α��� UI
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCUI_LOGIN* uiLogin;

	///< ä�ù� UI
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCUI_MAIN* uiMain;

	///< �� ��� UI
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCUI_ROOMLIST* uiRoomList;

	///< ���� UI
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCUI_ERROR* uiError;

	/**
	*@brief UI�ʱ�ȭ �� ��� ����.
	*@param[in] cModule �ش� ��ü�� ������.
	*/
	UFUNCTION(BlueprintCallable)
	void InitUI(AChatModule* cModule);

	/**
	*@brief �ش������ ��ȯ.
	*@param[in] sc_type �ش� ���� ��������.
	*/
	UFUNCTION(BlueprintCallable)
	void ChangeSceneTo(SC_TYPE sc_type);

	/**
	*@brief �˸�â �˾�.
	*@param[in] msg �˾�â�� �� �޼���.
	*/
	UFUNCTION(BlueprintCallable)
	void PopError(const FString& msg);

	/**
	*@brief �濡 �����Ѵ�.
	*@param[in] name ������ ���� �̸�
	*/
	UFUNCTION(BlueprintCallable)
	void EnterRoom(const FString& name);

	/**
	*@brief �� ���
	*@param[in] name ������ ���� �̸�
	*/
	UFUNCTION(BlueprintCallable)
	void EnterRoomList(const TArray<FString>& rooms);

	/**
	*@brief ���� ����� ����
	*@param[in] users ���� �̸����� �迭
	*/
	UFUNCTION(BlueprintCallable)
	void RefreshUserBox(const TArray<FString>& users);

	/**
	*@brief ���� ��Ͽ� ���� �߰�
	*@param[in] user �߰��� ���� �̸�
	*/
	UFUNCTION(BlueprintCallable)
	void AddUserBox(const FString& user);

	/**
	*@brief ���� ��Ͽ��� ���� ����
	*@param[in] user ������ ���� �̸�
	*/
	UFUNCTION(BlueprintCallable)
	void RemoveUserBox(const FString& user);

	/**
	*@brief ä��â�� �޼��� �߰�
	*@param[in] msg �߰��� �޼�����
	*/
	UFUNCTION(BlueprintCallable)
	void AddChatLog(const TArray<FString>& msgs);

protected:
	virtual void NativeConstruct() override;

private:
	class AChatModule* chatModule;
};
