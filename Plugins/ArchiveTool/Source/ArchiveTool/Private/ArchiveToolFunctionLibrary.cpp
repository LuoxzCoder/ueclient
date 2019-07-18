// Fill out your copyright notice in the Description page of Project Settings.


#include "ArchiveToolFunctionLibrary.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "JsonUtilities.h"
#include "Json.h"
FString UArchiveToolFunctionLibrary::ArchiveActorTransformbyTag(UObject *world, UClass *classtype, FName  tag)
{
	
	/////////////////////////////////////////////////////////////
	//////////
	FArchiveList archivelist;
	FArchiveList archivelist1;
	archivelist.name = "actorlist";
	TArray<AActor*> outactors;
	UGameplayStatics::GetAllActorsWithTag(world, tag, outactors);
	for (auto var : outactors)
	{
		FArchivestruct archivestruct;
		archivestruct.location = var->GetActorLocation();
		archivestruct.rotator = var->GetActorRotation();
		archivestruct.scale = var->GetActorScale3D();
		UStaticMeshComponent* umc = Cast<UStaticMeshComponent>(var->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		FString path = umc->GetStaticMesh()->GetPathName();
		archivestruct.staticmeshpath = path;	
		archivelist.objectlist.Add(archivestruct);
		//var->GetRootComponent();
	}
	FString outstring;
	FJsonObjectConverter::UStructToJsonObjectString<FArchiveList>(archivelist, outstring);

	//FJsonObjectConverter::JsonObjectStringToUStruct<FArchiveList>(outstring, &archivelist1, 0, 0);
	return outstring;
}