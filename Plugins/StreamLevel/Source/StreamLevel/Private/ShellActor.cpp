// Fill out your copyright notice in the Description page of Project Settings.


#include "ShellActor.h"
#include "Components/StaticMeshComponent.h"
#include "MyBlueprintFunctionLibrary.h"
#include"Engine.h"
#include "UnrealNetwork.h"
// Sets default values
AShellActor::AShellActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicateMovement = true;
	bReplicates = true;
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	PlaneMesh->SetupAttachment(RootComponent);
	PlaneMesh->SetMobility(EComponentMobility::Movable);
	PlaneMesh->SetSimulatePhysics(true);
	Tags.AddUnique("archive");

}
void AShellActor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to everyone
	DOREPLIFETIME(AShellActor, mmeshpath);
}
// Called when the game starts or when spawned
void AShellActor::BeginPlay()
{
	Super::BeginPlay();
	//FString path = "/Game/Geometry/Meshes/1M_Cube.1M_Cube";
	//UStaticMesh * sm = LoadObject<UStaticMesh>(nullptr, *path);
	//UStaticMesh * sm = LoadObject<UStaticMesh>(nullptr, *mmeshpath);
	//SetSaticMesh(sm);
	//SetSaticMesh(path);
	GetWorld()->GetTimerManager().SetTimer(th, this, &AShellActor::thworker, 1, false, 1);
}
void AShellActor::thworker()
{
	UMyBlueprintFunctionLibrary::CLogtofile(TEXT("thworker()"));
	UMyBlueprintFunctionLibrary::CLogtofile(*mmeshpath);
	UStaticMesh * sm = LoadObject<UStaticMesh>(nullptr, *mmeshpath);
	USetSaticMesh(sm);
	//GetWorld()->GetTimerManager().ClearTimer(th);
}
// Called every frame
void AShellActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AShellActor::USetSaticMesh(UStaticMesh * &mesh)
{
	PlaneMesh->SetStaticMesh(mesh);	// Set static mesh
}
//bool  AShellActor::SetSaticMesh_Validate(const FString& meshpath)
//{
//	return true;
//}
//void AShellActor::SetSaticMesh_Implementation(const FString& meshpath)
//{
//	UStaticMesh * sm = LoadObject<UStaticMesh>(nullptr, *meshpath);
//	USetSaticMesh(sm);
//	UMyBlueprintFunctionLibrary::CLogtofile(*meshpath);
//	UMyBlueprintFunctionLibrary::CLogtofile(TEXT("SetSaticMesh_Implementation"));
//
//}
//bool AShellActor::SetSaticMeshServer_Validate()
//{
//	return true;
//}
//void AShellActor::SetSaticMeshServer_Implementation()
//{
//	SetSaticMesh(mmeshpath);
//	UMyBlueprintFunctionLibrary::CLogtofile(TEXT("SetSaticMeshServer_Implementation()"));
//
//}