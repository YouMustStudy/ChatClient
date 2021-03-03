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

#include "ChatSocket.generated.h"

constexpr int32 BUF_SIZE = 2048;

UCLASS()
class CHATCLIENT_API AChatSocket : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChatSocket();

	UFUNCTION(BlueprintCallable, Category = "Socket")
	bool ConnectServer();

	UFUNCTION(BlueprintCallable, Category = "Socket")
	void SendMsg(UPARAM(ref) const FString& msg);

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeToMain();

	UFUNCTION(BlueprintImplementableEvent)
	void AddChatLog(const TArray<FString> &msg);

	UFUNCTION(BlueprintImplementableEvent)
	void AddErrorLog(const FString& msg);

	UFUNCTION(BlueprintImplementableEvent)
	void EnterRoom(const FString& msg);

	UFUNCTION(BlueprintImplementableEvent)
	void EnterRoomList(const TArray<FString> &rooms);

	UFUNCTION(BlueprintImplementableEvent)
	void RefreshUserList(const TArray<FString>& users);

	UFUNCTION(BlueprintImplementableEvent)
	void RemoveUserBox(const FString& user);

	UFUNCTION(BlueprintImplementableEvent)
	void AddUserBox(const FString& user);

private:
	FSocket* m_socket{ nullptr };
	ANSICHAR m_buffer[BUF_SIZE];
	ANSICHAR m_mbcsBuffer[BUF_SIZE];
	atomic_bool m_online{ false };
	TQueue<FString, EQueueMode::Spsc> m_recvQueue;
	vector<thread> m_threads;

	void recvThread();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
