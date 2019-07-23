// Fill out your copyright notice in the Description page of Project Settings.


#include "SLGameMode.h"
#include "MyBlueprintFunctionLibrary.h"
#include "Engine.h"


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

}

FString ASLGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString restr = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	SplitString(Options);
	UMyBlueprintFunctionLibrary::CLogtofile(TEXT("ASLGameMode::InitNewPlayer"));
	UMyBlueprintFunctionLibrary::CLogtofile(Options); 
	UMyBlueprintFunctionLibrary::CLogtofile(restr);
	loadandunloadstreaminglevel(*strarray[0]);
////////////////////////////////////////////////////////
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
///////////////////////////////////////////////
	return restr;
}

