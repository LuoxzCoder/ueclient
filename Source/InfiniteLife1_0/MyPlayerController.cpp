// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Engine/LevelStreaming.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
void AMyPlayerController::openstreamlevel(FName levename)
{
	//opensublevel(levelname);
	//const TArray<ULevelStreaming*>& StreamedLevels = GetWorld()->GetStreamingLevels();
	//for (int i = 0; i < StreamedLevels.Num(); i++)
	//{
	//	GetWorld()->RemoveStreamingLevelAt(i);
	//}
	//FName levename = "/Game/TwinStickBP/Maps/TwinStickExampleMap";
	ULevelStreamingDynamic* StreamingLevel = static_cast<ULevelStreamingDynamic*>(StaticConstructObject_Internal(ULevelStreamingDynamic::StaticClass(), GetWorld(), NAME_None, RF_NoFlags));
	StreamingLevel->SetWorldAssetByPackageName(levename);
	StreamingLevel->LevelColor = FColor::MakeRandomColor();
	StreamingLevel->bShouldBlockOnLoad = false;
	StreamingLevel->bInitiallyLoaded = false;
	StreamingLevel->bInitiallyVisible = false;
	//StreamingLevel->LevelTransform = // where to put it

	StreamingLevel->PackageNameToLoad = levename;// PackageName containing level to load

	FString PackageFileName;
	if (!FPackageName::DoesPackageExist(StreamingLevel->PackageNameToLoad.ToString(), NULL, &PackageFileName))
	{
		//	//UE_LOG(LogStreamingLevel, Error, TEXT("trying to load invalid level %s"), *StreamingLevel->PackageNameToLoad.ToString());
	}

	StreamingLevel->PackageNameToLoad = FName(*FPackageName::FilenameToLongPackageName(PackageFileName));
	// Add the new level to world.
	GetWorld()->AddStreamingLevel(StreamingLevel);
	UGameplayStatics::LoadStreamLevel(this, levename, true, false, FLatentActionInfo());
}
void AMyPlayerController::loadstreamlevel(FName levelname)
{
	UGameplayStatics::LoadStreamLevel(this, levelname, true, false, FLatentActionInfo());

}
void AMyPlayerController::unloadstreamlevel(TArray<FName> levelnames)
{
	for (auto var : levelnames)
	{
	UGameplayStatics::UnloadStreamLevel(this, var, FLatentActionInfo(), false);
	}

}
bool AMyPlayerController::opensublevel_Validate(FName levelname)
{
	return true;
}
void AMyPlayerController::opensublevel_Implementation(FName levename)
{
	const TArray<ULevelStreaming*>& StreamedLevels = GetWorld()->GetStreamingLevels();
	for (int i = 0; i < StreamedLevels.Num(); i++)
	{
		GetWorld()->RemoveStreamingLevelAt(i);
	}
	//FName levename = "/Game/TwinStickBP/Maps/TwinStickExampleMap";
	ULevelStreamingDynamic* StreamingLevel = static_cast<ULevelStreamingDynamic*>(StaticConstructObject_Internal(ULevelStreamingDynamic::StaticClass(), GetWorld(), NAME_None, RF_NoFlags));
	StreamingLevel->SetWorldAssetByPackageName(levename);
	StreamingLevel->LevelColor = FColor::MakeRandomColor();
	StreamingLevel->bShouldBlockOnLoad = false;
	StreamingLevel->bInitiallyLoaded = false;
	StreamingLevel->bInitiallyVisible = false;
	//StreamingLevel->LevelTransform = // where to put it

	StreamingLevel->PackageNameToLoad = levename;// PackageName containing level to load

	FString PackageFileName;
	if (!FPackageName::DoesPackageExist(StreamingLevel->PackageNameToLoad.ToString(), NULL, &PackageFileName))
	{
		//	//UE_LOG(LogStreamingLevel, Error, TEXT("trying to load invalid level %s"), *StreamingLevel->PackageNameToLoad.ToString());
	}

	StreamingLevel->PackageNameToLoad = FName(*FPackageName::FilenameToLongPackageName(PackageFileName));
	// Add the new level to world.
	GetWorld()->AddStreamingLevel(StreamingLevel);
	UGameplayStatics::LoadStreamLevel(this, levename, true, false, FLatentActionInfo());
}
