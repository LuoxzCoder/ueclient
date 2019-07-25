// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "StreamLevelPC.generated.h"

/**
 * 
 */
UCLASS()
class STREAMLEVEL_API AStreamLevelPC : public APlayerController
{
	GENERATED_BODY()
public:
	UPROPERTY()
		TArray<AActor*> actorarray;
};
