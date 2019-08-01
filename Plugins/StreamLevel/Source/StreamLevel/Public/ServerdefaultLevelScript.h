// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "ServerdefaultLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class STREAMLEVEL_API AServerdefaultLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
		class UUTcpCommunicatorv2* matchclient;
        class UTcpGameInstance* tcpgameinstance; 
protected:
	virtual void BeginPlay() override;
};
