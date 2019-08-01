// Fill out your copyright notice in the Description page of Project Settings.


#include "UTcpCommunicatorv2.h"
#include "TcpClientv.h"
#include "Engine.h"
#include "JsonUtilities.h"
#include "Json.h"
#include "MyBlueprintFunctionLibrary.h"

#include "TcpGameInstance.h"
class TcpClientv* UUTcpCommunicatorv2::mtcp = nullptr;
void UUTcpCommunicatorv2::clientexit()
{
	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::EXITGAME;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	if (UUTcpCommunicatorv2::mtcp == nullptr)
	{
		return;
	}
	UUTcpCommunicatorv2::mtcp->Send(outstring);
	FPlatformProcess::Sleep(0.03);
	UMyBlueprintFunctionLibrary::CLogtofile(FString("OnGameEndevent.Broadcast();"));
	UUTcpCommunicatorv2::mtcp->exitthread = true;
}
void UUTcpCommunicatorv2::init()
{
	UMyBlueprintFunctionLibrary::AddfunctiontoOnGameexitArray(&UUTcpCommunicatorv2::clientexit);

	UGameInstance* gameinstance = world->GetGameInstance();
	tcpgameinstance = Cast<UTcpGameInstance>(gameinstance);
	check(tcpgameinstance);
	//tcpclient = tcpgameinstance->GetSignUpLoginClient();
	//check(tcpclient);
	//tcpclient->OnFileReceiveSucceed.AddDynamic(this, &UUTcpCommunicatorv2::onfilereceivesucceed);
}
void UUTcpCommunicatorv2::OnTcpResponse(const TArray<uint8>&p, const FString & str)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *str);
	FMessagePackage mp;
	FJsonObjectConverter::JsonObjectStringToUStruct<FMessagePackage>(str, &mp, 0, 0);
	if (mp.MT == MessageType::EntryMAP)
	{
		FString pld = mp.PayLoad;

		FString param = FString::Printf(TEXT("?%s?%s"), *LevelShouldBeLoaded, *tcpgameinstance->username);
		pld.Append(param);
		UGameplayStatics::OpenLevel(world, *pld);
		//UGameplayStatics::OpenLevel(GetWorld(), "192.168.1.240:7788");
		//FString outstring;
		//mp.MT = MessageType::EntryMAPOK;
		//FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(mp, outstring);
		//mtcp->Send(outstring);
	}
}
//void UUTcpCommunicatorv2::onfilereceivesucceed(FString &filecontent, MessageType type)
//{
//	//type :mean file type;
//	this->filecontent = filecontent;
//	OpenServermap(mapname);
//	//UMyBlueprintFunctionLibrary::CLogtofile(FString("onfilereceivesucceed();"));
//
//}
void UUTcpCommunicatorv2::OpenServermap(FString pmapname, FString mapID, FString nvn)
{
	FMessagePackage messagepackage(MessageType::MATCH, FString("hi"));
	LevelShouldBeLoaded = pmapname;
	if (mtcp)
	{	
		FString outstring;
		messagepackage.MT = MessageType::EXITGAME;
		FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
		mtcp->Send(outstring);
		UMyBlueprintFunctionLibrary::CLogtofile(FString("OnGameEndevent.Broadcast();"));
		mtcp->exitthread = true;
		FPlatformProcess::Sleep(0.03);
		mtcp = nullptr;
	}
	mtcp = new TcpClientv();

		FString outstring;
		messagepackage.MT = MessageType::MATCH;
		messagepackage.PayLoad = LevelShouldBeLoaded+"?"+mapID+"?"+nvn;
		FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
		mtcp->Connecttoserver(192, 168, 1, 240, 8001);
		mtcp->OnTcpClientReceiveddata.AddDynamic(this, &UUTcpCommunicatorv2::OnTcpResponse);
		mtcp->Send(outstring);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *outstring);
}
void UUTcpCommunicatorv2::EntyMapOkMessage()
{
	FMessagePackage mp;
	FString outstring;
	mp.MT = MessageType::EntryMAPOK;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(mp, outstring);
	mtcp->Send(outstring);
}
//FString UUTcpCommunicatorv2::GetMapArchiveInfor(FString name)
//{
//	check(tcpclient);
//	tcpclient->GetMapActorInforfile(name);
//	return "";
//}
