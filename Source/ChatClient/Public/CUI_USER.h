// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "CUI_USER.generated.h"

/**
 *
 */
UCLASS()
class CHATCLIENT_API UCUI_USER : public UUserWidget
{
	GENERATED_BODY()

public:
	///>���� �̸��� ��Ÿ���� ��ü
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* userName;
	///>���� �ӼӸ��� ���� ��ư
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		UButton* userMsgButton;
	
	/**
	*@brief ���� �̸��� �����ϴ� �Լ�.
	*@param[in] name ������ ���ڿ�
	*/
	UFUNCTION(BlueprintCallable)
		void SetName(const FString& name);

	/**
	*@brief ä�� �Է¹ڽ��� �ӼӸ� Ŀ�ǵ� ����
	*/
	UFUNCTION(BlueprintCallable)
		void SetMsgCommand();

	///>����ȭ�� UI
	UPROPERTY(BlueprintReadWrite)
		class UCUI_MAIN* uiMain;

protected:
	virtual void NativeConstruct() override;
};
