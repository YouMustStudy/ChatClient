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

#include "ChatModule.generated.h"

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
	HELP,
	SUFFIX
};

UCLASS()
class CHATCLIENT_API AChatModule : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChatModule();

	///< ��ü ���� UI
	UPROPERTY(EditDefaultsOnly, Category = "SubClass")
		TAssetSubclassOf<class UCUI_TOTAL> UITotalClass;

	/**
	*@brief ������ �����Ѵ�.
	*param[in] address IPŸ���� �ּ�
	*param[in] port ��Ʈ��ȣ
	*return ���� ���� ���� ����.
	*/
	UFUNCTION(BlueprintCallable, Category = "Socket")
		bool ConnectServer(const FString& address, int32 port);

	/**
	*@brief ������ �޼����� ����
	*param[in] msg ���� �޼���
	*/
	UFUNCTION(BlueprintCallable, Category = "Socket")
		void SendMsg(UPARAM(ref) const FString& msg);

	///< ��ü ���� UI
	UPROPERTY(BlueprintReadWrite)
		UCUI_TOTAL* uiTotal;

	void Disconnect();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FSocket* m_socket{ nullptr };						///< �𸮾� ����
	ANSICHAR m_buffer[BUF_SIZE];						///< recv ����
	ANSICHAR m_mbcsBuffer[BUF_SIZE];					///< WCS to MBCS ����
	atomic_bool m_online{ false };						///< ���� �¶����ΰ�?
	TQueue<FString, EQueueMode::Spsc> m_recvQueue;		///< �Ľ��� ���ڿ����� �����ϴ� ��ü
	vector<thread> m_threads;							///< ������ ���� �����̳�
	TArray<FString> m_commands;							///< ������ ��ſ� �ʿ��� Ŀ�ǵ���� ����� �����̳�

	void recvThread();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;


};
