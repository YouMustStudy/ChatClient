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

	/**
	*@brief MBCS���� UNICODE�� ��ȯ�ϴ� �Լ�
	*param[in] str ��ȯ�� MBCS ���ڿ�
	*param[in] loc ��ȯ �� ����� ������
	*return UNICODE ���ڿ�
	*/
	wstring MbsToWcs(const string& str, const locale& loc = std::locale(""));

	/**
	*@brief UNICODE���� MBCS�� ��ȯ�ϴ� �Լ�
	*param[in] str ��ȯ�� UNICODE ���ڿ�
	*param[in] loc ��ȯ �� ����� ������
	*return MBCS ���ڿ�
	*/
	string WcsToMbs(const wstring& str, const locale& loc = std::locale(""));
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
};
