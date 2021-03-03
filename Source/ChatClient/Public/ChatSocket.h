// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include <string>
#include <cuchar>
#include <clocale>
#include <atomic>
#include <vector>
#include <thread>
using namespace std;

#include "Containers/Queue.h"
#include "Engine.h"
#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Blueprint/UserWidget.h"
#include "CUI_TOTAL.h"

#include "ChatSocket.generated.h"

constexpr int32 BUF_SIZE = 2048;

UENUM()
enum class CMD_TYPE : uint8
{
	LOGIN,
	ERROR,
	ROOMENTER,
	ROOMLIST,
	USERLIST,
	USERENTER,
	USERLEAVE,
	SUFFIX
};

UCLASS()
class CHATCLIENT_API AChatModule : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChatModule();

	///< 전체 메인 UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SubClass")
		TAssetSubclassOf<class UCUI_TOTAL> UITotalClass;

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

private:
	FSocket* m_socket{ nullptr };
	ANSICHAR m_buffer[BUF_SIZE];
	ANSICHAR m_mbcsBuffer[BUF_SIZE];
	atomic_bool m_online{ false };
	TQueue<FString, EQueueMode::Spsc> m_recvQueue;
	vector<thread> m_threads;
	TArray<FString> m_commands;

	void recvThread();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
