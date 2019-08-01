// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UMG.h"
#include "mainui_cpp.generated.h"

/**
 * 
 */
UCLASS()
class INFINITELIFE1_0_API Umainui_cpp : public UUserWidget
{
	GENERATED_BODY()
	FString url = "192.168.1.240:8002";
	class UTcpGameInstance* tcpgameinstance;
	class UTcpCommunicatorv1* tcpclient;
public:
	virtual void NativePreConstruct()override;
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* mButtonItem;
private:
	UFUNCTION()
		void Onpressed_mButtonItem();
};
