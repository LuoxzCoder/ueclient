// Fill out your copyright notice in the Description page of Project Settings.


#include "SLGameMode.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Engine.h"
#include "ArchiveToolFunctionLibrary.h"
#include "JsonUtilities.h"
#include "Json.h"
#include "ShellActor.h"
#include "StreamLevelPC.h"

void ASLGameMode::SplitString(FString str)
{//////?xxxxx?xxxxx?xxxxx...
	FString str1;
	FString str2;
	str.Split("?", &str1, &str2, ESearchCase::IgnoreCase, ESearchDir::FromEnd);
	strarray.Insert(str2, 0);
	if (!str1.IsEmpty())
	{
		SplitString(str1);
	}
}
void ASLGameMode::loadandunloadstreaminglevel(FName levelname)
{
	willloadlevelname = levelname;
	FLatentActionInfo info;
	info.CallbackTarget = this;
	info.ExecutionFunction = "ClearpreLevelandLoadstreamlevelv1";
	info.UUID = 1;
	info.Linkage = 0;

	UMyBlueprintFunctionLibrary::CLogtofile(FString::FromInt(indexoflevel).Append("    indexoflevel"));
	const TArray<ULevelStreaming*>& StreamedLevels = GetWorld()->GetStreamingLevels();
	if (StreamedLevels.Num() == 0)
	{
		UMyBlueprintFunctionLibrary::CLogtofile(TEXT("StreamedLevels.Num() == 0"));
		indexoflevel = 0;
		return;
	}
	if (indexoflevel == StreamedLevels.Num())
	{
		indexoflevel = 0;
		UMyBlueprintFunctionLibrary::CLogtofile(TEXT("indexoflevel == StreamedLevels.Num()"));
		return;
	}
	bool b = StreamedLevels[indexoflevel]->GetWorldAssetPackageFName().IsEqual(levelname);
	if (b)
	{
		if (StreamedLevels[indexoflevel]->IsLevelLoaded())
		{
			indexoflevel++;
			loadandunloadstreaminglevelv1(willloadlevelname);
		}
		else
		{
			UMyBlueprintFunctionLibrary::CLogtofile(TEXT("UGameplayStatics::LoadStreamLevel(this, StreamedLevels[indexoflevel]->GetWorldAssetPackageFName(), true, true, info)"));
			UGameplayStatics::LoadStreamLevel(this, StreamedLevels[indexoflevel]->GetWorldAssetPackageFName(), true, true, info);
			indexoflevel++;
		}
	}
	else
	{
		if (StreamedLevels[indexoflevel]->IsLevelLoaded())
		{
			UGameplayStatics::UnloadStreamLevel(this, StreamedLevels[indexoflevel]->GetWorldAssetPackageFName(), info, true);
			UMyBlueprintFunctionLibrary::CLogtofile(TEXT("blueprintunloadlevel(StreamedLevels[0]->GetWorldAssetPackageFName())"));
			indexoflevel++;
		}
		else
		{
			indexoflevel++;
			loadandunloadstreaminglevelv1(willloadlevelname);
		}
	}
}
void ASLGameMode::loadandunloadstreaminglevelv1(FName levelname)
{
	UMyBlueprintFunctionLibrary::CLogtofile(willloadlevelname.ToString().Append(" before"));
	loadandunloadstreaminglevel(willloadlevelname);
	UMyBlueprintFunctionLibrary::CLogtofile(willloadlevelname.ToString().Append(" after"));
}

void ASLGameMode::OnfileReceiveComplete(FString& file, MessageType type)
{
	UMyBlueprintFunctionLibrary::CLogtofile(TEXT("OnfileReceiveComplete"));
	UMyBlueprintFunctionLibrary::CLogtofile(*file);
	FArchiveList archivelist;
	FJsonObjectConverter::JsonObjectStringToUStruct<FArchiveList>(file, &archivelist, 0, 0);
	for (auto var : archivelist.objectlist)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform transform(var.rotator, var.location, var.scale);
	    AShellActor *pactor = (AShellActor*)GetWorld()->SpawnActor<AActor>(AShellActor::StaticClass(),transform, ActorSpawnParams);
		pactor->SetOwner(playercontroller);
		pactor->mmeshpath = var.staticmeshpath;

		//APlayerController* apc = GetWorld()->GetFirstPlayerController();
		//check(apc);
		//AStreamLevelPC* astlpc = Cast<AStreamLevelPC>(apc);
		//check(astlpc);
		//astlpc->actorarray.Add(pactor);


		//pactor->SetSaticMesh(var.staticmeshpath);
		//pactor->SetActorScale3D(var.scale);
		//UStaticMesh * sm = LoadObject<UStaticMesh>(nullptr, *var.staticmeshpath);
		//spawnv1(var.location,var.rotator,var.scale, sm);
	}

}

FString ASLGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString restr = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	SplitString(Options);
	UMyBlueprintFunctionLibrary::CLogtofile(TEXT("ASLGameMode::InitNewPlayer"));
	UMyBlueprintFunctionLibrary::CLogtofile(Options); 
	UMyBlueprintFunctionLibrary::CLogtofile(restr);
	UMyBlueprintFunctionLibrary::CLogtofile(*strarray[0]);
	UMyBlueprintFunctionLibrary::CLogtofile(*strarray[1]);
	loadandunloadstreaminglevel(*strarray[0]);
////////////////////////////////////////////////////////
	if (tcpclient != nullptr)
	{
		return restr;
	}
	UGameInstance* gameinstance = GetWorld()->GetGameInstance();
	if (gameinstance == nullptr)
	{
		UMyBlueprintFunctionLibrary::CLogtofile(TEXT("gameinstance is null"));
	}
	else
	{
		UMyBlueprintFunctionLibrary::CLogtofile(TEXT("gameinstance is not null"));

	}
	UTcpGameInstance* tcpgameinstance = Cast<UTcpGameInstance>(gameinstance);
	if (tcpgameinstance == nullptr)
	{
		UMyBlueprintFunctionLibrary::CLogtofile(TEXT("tcpgameinstance is null"));
	}
	else
	{
		UMyBlueprintFunctionLibrary::CLogtofile(TEXT("tcpgameinstance is not null"));

	}
	check(tcpgameinstance);
	tcpclient = tcpgameinstance->GetSignUpLoginClient();
	check(tcpclient);
	tcpclient->OnFileReceiveSucceed.AddDynamic(this, &ASLGameMode::OnfileReceiveComplete);
	tcpclient->ConnectServer();
	FString params = strarray[0].Replace(TEXT("/"), TEXT("_")) + "?" + strarray[1];
	tcpclient->GetMapActorInforfile(params);

	playercontroller = NewPlayerController;
///////////////////////////////////////////////
	return restr;
}

