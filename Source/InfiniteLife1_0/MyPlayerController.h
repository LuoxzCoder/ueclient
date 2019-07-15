// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class INFINITELIFE1_0_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void loadstreamlevel(FName levelname);
	UFUNCTION(BlueprintCallable)
		void unloadstreamlevel(TArray<FName> levelnames);
	UFUNCTION(BlueprintCallable)
		void openstreamlevel(FName levelname);
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable)
	void opensublevel(FName levelname);
	virtual bool opensublevel_Validate(FName levelname);
	virtual void opensublevel_Implementation(FName levelname);
};
