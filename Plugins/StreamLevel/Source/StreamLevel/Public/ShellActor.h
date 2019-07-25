// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShellActor.generated.h"

UCLASS()
class STREAMLEVEL_API AShellActor : public AActor
{
	GENERATED_BODY()
		UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* PlaneMesh;
	FTimerHandle th;
	void thworker();
public:	
	// Sets default values for this actor's properties
	AShellActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(Replicated)
	FString mmeshpath;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void USetSaticMesh(UStaticMesh *& mesh);
	//UFUNCTION(NetMulticast,Reliable,WithValidation)
	//void SetSaticMesh(const FString& meshpath);
	//UFUNCTION(Server, Reliable, WithValidation)
	//void SetSaticMeshServer();
};
