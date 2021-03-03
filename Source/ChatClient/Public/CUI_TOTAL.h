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
	///< 로그인 UI
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCUI_LOGIN* uiLogin;

	///< 채팅방 UI
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCUI_MAIN* uiMain;

	///< 방 목록 UI
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCUI_ROOMLIST* uiRoomList;

	///< 에러 UI
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCUI_ERROR* uiError;

	/**
	*@brief UI초기화 및 모듈 설정.
	*@param[in] cModule 해당 객체의 포인터.
	*/
	UFUNCTION(BlueprintCallable)
	void InitUI(AChatModule* cModule);

	/**
	*@brief 해당씬으로 전환.
	*@param[in] sc_type 해당 씬의 열거형값.
	*/
	UFUNCTION(BlueprintCallable)
	void ChangeSceneTo(SC_TYPE sc_type);

	/**
	*@brief 알림창 팝업.
	*@param[in] msg 팝업창에 들어갈 메세지.
	*/
	UFUNCTION(BlueprintCallable)
	void PopError(const FString& msg);

	/**
	*@brief 방에 입장한다.
	*@param[in] name 입장한 방의 이름
	*/
	UFUNCTION(BlueprintCallable)
	void EnterRoom(const FString& name);

	/**
	*@brief 방 목록
	*@param[in] name 입장한 방의 이름
	*/
	UFUNCTION(BlueprintCallable)
	void EnterRoomList(const TArray<FString>& rooms);

	/**
	*@brief 유저 목록을 갱신
	*@param[in] users 유저 이름들의 배열
	*/
	UFUNCTION(BlueprintCallable)
	void RefreshUserBox(const TArray<FString>& users);

	/**
	*@brief 유저 목록에 유저 추가
	*@param[in] user 추가할 유저 이름
	*/
	UFUNCTION(BlueprintCallable)
	void AddUserBox(const FString& user);

	/**
	*@brief 유저 목록에서 유저 제거
	*@param[in] user 제거할 유저 이름
	*/
	UFUNCTION(BlueprintCallable)
	void RemoveUserBox(const FString& user);

	/**
	*@brief 채팅창에 메세지 추가
	*@param[in] msg 추가할 메세지들
	*/
	UFUNCTION(BlueprintCallable)
	void AddChatLog(const TArray<FString>& msgs);

protected:
	virtual void NativeConstruct() override;

private:
	class AChatModule* chatModule;
};
