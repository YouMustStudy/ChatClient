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
	///< 채팅 로그를 표시할 UI 객체
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
		TAssetSubclassOf<class UCUI_LOG> UILogClass;

	///< 접속자를 표시할 UI 객체
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
		TAssetSubclassOf<class UCUI_USER> UIUserClass;

	///< 채팅로그가 표시되는 ScrollBox
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* chatBox;

	///< 접속한 유저들이 표시되는 ScrollBox
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UScrollBox* userBox;

	///< 접속한 방 이름이 표시되는 TextBlock
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* roomNameText;

	///< 메세지를 입력할 입력박스
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UEditableTextBox* inputMsgBox;

	///< 보내기 버튼
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* sendButton;

	///< 방 목록 버튼
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* roomButton;

	///< 메인 모듈
	UPROPERTY(BlueprintReadWrite)
		class AChatModule* chatModule;

	/**
	*@brief 방제목을 설정하는 함수.
	*@param[in] name 설정할 방 이름.
	*/
	UFUNCTION(BlueprintCallable)
		void SetRoomName(const FString& name);

	/**
	*@brief 방제목을 설정하는 함수.
	*@param[in] name 설정할 방 이름.
	*/
	UFUNCTION(BlueprintCallable)
		void ClearInputMsgBox();

	/**
	*@brief 입력값을 기반으로 채팅을 전송하는 함수.
	*/
	UFUNCTION(BlueprintCallable)
		void SendChat();

	/**
	*@brief 채팅 입력창을 특정 문자열로 설정하는 함수.
	*@param[in] msg 설정할 문자열.
	*/
	UFUNCTION(BlueprintCallable)
		void SetInputMsgBox(const FString& msg);

	/**
	*@brief 문자열을 채팅창에 추가하는 함수.
	*@param[in] msg 추가할 문자열.
	*/
	UFUNCTION(BlueprintCallable)
		void AddChatLog(UPARAM(ref) const FString& msg, FLinearColor color = FLinearColor(0, 0, 0, 1.0));

	/**
	*@brief 채팅창을 초기화하는 함수.
	*/
	UFUNCTION(BlueprintCallable)
		void ClearChatLog();

	/**
	*@brief 입장한 유저를 유저 목록에 등록하는 함수
	*@param[in] user 입장 유저의 이름 문자열
	*/
	UFUNCTION(BlueprintCallable)
		void AddUserBox(const FString& user);

	/**
	*@brief 퇴장한 유저를 유저 목록에서 삭제하는 함수
	*@param[in] user 퇴장 유저의 이름 문자열
	*/
	UFUNCTION(BlueprintCallable)
		void RemoveUserBox(const FString& user);

	/**
	*@brief 유저 목록을 새로 초기화하는 함수.
	*@param[in] users 초기화 한 후 추가될 유저들의 이름 배열
	*/
	UFUNCTION(BlueprintCallable)
		void RefreshUserBox(UPARAM(ref) const TArray<FString>& users);

	/**
	*@brief 유저 목록을 요청하는 함수.
	*/
	UFUNCTION(BlueprintCallable)
		void RequestRoomList();

	/**
	*@brief 메세지 입력창에서 엔터 시 호출되는 함수.
	*/
	UFUNCTION(BlueprintCallable)
		void InputMsgBoxOnTextCommitted(const FText& InText, ETextCommit::Type InCommitType);

private:
	virtual void NativeConstruct() override;

	///< 유저목록을 관리하는 테이블.
	TMap<FString, UCUI_USER*> userTable;
};
