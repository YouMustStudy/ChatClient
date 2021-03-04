// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <string>
#include <cuchar>
#include <locale>
#include <atomic>
#include <vector>
#include <thread>
#include <codecvt>
using namespace std;

#include "Containers/Queue.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "CUI_TOTAL.h"

#include "ChatModule.generated.h"

constexpr int32 BUF_SIZE = 2048;

UENUM()
enum class CMD_TYPE : uint8
{
	SERVEROFFLINE,
	LOGINERROR,
	ERROR,
	ROOMENTER,
	ROOMLIST,
	USERLIST,
	USERENTER,
	USERLEAVE,
	HELP,
	MSG,
	SUFFIX
};

UCLASS()
class CHATCLIENT_API AChatModule : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChatModule();

	/**
	*@brief 서버에 연결한다.
	*param[in] address IP타입의 주소
	*param[in] port 포트번호
	*return 서버 연결 성공 여부.
	*/
	UFUNCTION(BlueprintCallable, Category = "Socket")
		bool ConnectServer(const FString& address, int32 port);

	/**
	*@brief 서버에 메세지를 전송
	*param[in] msg 보낼 메세지
	*/
	UFUNCTION(BlueprintCallable, Category = "Socket")
		void SendMsg(UPARAM(ref) const FString& msg);

	///< 전체 메인 UI
	UPROPERTY(BlueprintReadWrite)
		UCUI_TOTAL* uiTotal;

	void Disconnect();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FSocket* m_socket{ nullptr };						///< 언리얼 소켓
	ANSICHAR m_buffer[BUF_SIZE];						///< recv 버퍼
	ANSICHAR m_mbcsBuffer[BUF_SIZE];					///< WCS to MBCS 버퍼
	atomic_bool m_online{ false };						///< 지금 온라인인가?
	TQueue<FString, EQueueMode::Spsc> m_recvQueue;		///< 파싱한 문자열들을 저장하는 객체
	vector<thread> m_threads;							///< 스레드 저장 컨테이너
	TArray<FString> m_commands;							///< 서버와 통신에 필요한 커맨드들이 저장된 컨테이너

	void recvThread();

	/**
	*@brief MBCS에서 UNICODE로 변환하는 함수
	*param[in] str 변환할 MBCS 문자열
	*param[in] loc 변환 시 사용할 로케일
	*return UNICODE 문자열
	*/
	wstring MbsToWcs(const string& str, const locale& loc = std::locale(""));

	/**
	*@brief UNICODE에서 MBCS로 변환하는 함수
	*param[in] str 변환할 UNICODE 문자열
	*param[in] loc 변환 시 사용할 로케일
	*return MBCS 문자열
	*/
	string WcsToMbs(const wstring& str, const locale& loc = std::locale(""));
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};
