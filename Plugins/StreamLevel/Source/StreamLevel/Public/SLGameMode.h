// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "TcpCommunicatorv1.h"
#include "TcpGameInstance.h"
#include "SLGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STREAMLEVEL_API ASLGameMode : public AGameMode
{
	GENERATED_BODY()
	class UTcpCommunicatorv1* tcpclient; 
	TArray<FString> strarray;
	void SplitString(FString str);
private:
	FName willloadlevelname;
	int indexoflevel = 0;
	void loadandunloadstreaminglevel(FName levelname);
	UFUNCTION()
	void loadandunloadstreaminglevelv1(FName levelname);
	UFUNCTION()
	void OnfileReceiveComplete( FString& file, MessageType type);
protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT(""))override;
};
