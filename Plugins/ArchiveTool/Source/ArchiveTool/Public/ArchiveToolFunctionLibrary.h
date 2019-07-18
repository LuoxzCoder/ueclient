// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ArchiveToolFunctionLibrary.generated.h"

//struct Archivescomponenttruct {
//	
//		TArray<Archivescomponenttruct> staticmeshpaths;
//		
//		FString staticmeshpath;
//
//		FVector  location;
//
//		FRotator rotator;
//	
//		FVector scale;
//};
//struct ArchiveactorList {
//
//	TArray<Archivescomponenttruct> objectlist;
//};



USTRUCT()
struct FArchivestruct {
	GENERATED_BODY()

	UPROPERTY()
		FString staticmeshpath;
	UPROPERTY()
		FVector  location;
	UPROPERTY()
		FRotator rotator;
	UPROPERTY()
		FVector scale;
	FArchivestruct() {
		staticmeshpath = "";
		location = FVector::ZeroVector;
		rotator = FRotator::ZeroRotator;
		scale = FVector::ZeroVector;
	}
};
USTRUCT()
struct FArchiveList {
	GENERATED_BODY()
	UPROPERTY()
		FString  name;
	UPROPERTY()
		TArray<FArchivestruct> objectlist;


	FArchiveList() {
		objectlist.Empty();
		name = "";
	}

};
/**
 * 
 */
UCLASS()
class ARCHIVETOOL_API UArchiveToolFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Mybp")
		static FString ArchiveActorTransformbyTag(UObject *world, UClass *classtype, FName  tag);
};
