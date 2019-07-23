// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TcpGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TCPSCENV1_API UTcpGameInstance : public UGameInstance
{
	GENERATED_BODY()
		UTcpGameInstance(const FObjectInitializer& ObjectInitializer);
	UPROPERTY()
	class UTcpCommunicatorv1 *SignUpLoginClient=nullptr;
	UPROPERTY()
	class UUTcpCommunicatorv2 *MatchClient = nullptr;
public:
	UTcpCommunicatorv1 * GetSignUpLoginClient();
	UUTcpCommunicatorv2 * GetMatchClient();
	FString username;
	FString password;
};
