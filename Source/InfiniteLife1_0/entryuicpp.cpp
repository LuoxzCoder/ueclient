// Fill out your copyright notice in the Description page of Project Settings.


#include "entryuicpp.h"
#include "TcpClientv.h"
#include "JsonUtilities.h"
#include "Json.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "MyBlueprintFunctionLibrary.h"
#include "HttpServicev.h"
bool Uentryuicpp::connected = false;
class TcpClientv* Uentryuicpp::mtcp = nullptr;
FString Uentryuicpp::LevelShouldBeLoaded="";
Uentryuicpp::Uentryuicpp(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{

}
void Uentryuicpp::clientexit()
{
	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::EXITGAME;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	Uentryuicpp::mtcp->Send(outstring);
	//Uentryuicpp::mtcp->Send((uint8*)outstring.GetCharArray().GetData(),outstring.Len()*2);
	UMyBlueprintFunctionLibrary::CLogtofile(FString("OnGameEndevent.Broadcast();"));
	Uentryuicpp::mtcp->exitthread = true;

}
void Uentryuicpp::clientexit1()
{
	UMyBlueprintFunctionLibrary::CLogtofile(FString("Uentryuicpp::clientexit1()"));

}
void Uentryuicpp::NativePreConstruct()
{
	if (mButtonItem)
	{
		mButtonItem->OnClicked.AddDynamic(this, &Uentryuicpp::Onpressed_mButtonItem);
	}
	if (mButtonItem1)
	{
		mButtonItem1->OnClicked.AddDynamic(this, &Uentryuicpp::Onpressed_mButtonItem1);
	}
}
void Uentryuicpp::NativeConstruct()
{
	if (mtcp == nullptr)
	{
		mtcp = new TcpClientv();

		UMyBlueprintFunctionLibrary::AddfunctiontoOnGameexitArray(&Uentryuicpp::clientexit);
		UMyBlueprintFunctionLibrary::AddfunctiontoOnGameexitArray(&Uentryuicpp::clientexit1);
	}

	//http->OnHttpResponseComplete.AddDynamic(this, &Uentryuicpp::OnHttpResponse_completed);
	//http->HttpGet("http://192.168.1.240/file/file.rar");
}
void Uentryuicpp::OnHttpResponse_completed(const FString& Responsestring, const TArray<uint8>& Responsecontent, UObject* extra)
{
	UMyBlueprintFunctionLibrary::writedatatofile(FString("d:/ue.rar"), Responsecontent);
}
void Uentryuicpp::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{

}

void Uentryuicpp::Onpressed_mButtonItem()
{
	FMessagePackage mp(MessageType::MATCH,FString("hi"));
	LevelShouldBeLoaded = "/Game/FirstPersonBP/Maps/FirstPersonExampleMap";
	if (!connected)
	{
		FString outstring;
		messagepackage.MT = MessageType::MATCH;
		messagepackage.PayLoad = LevelShouldBeLoaded;
		FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
		connected = mtcp->Connecttoserver(192, 168, 1, 240, 8001);
		mtcp->OnTcpClientReceiveddata.AddDynamic(this, &Uentryuicpp::OnTcpResponse);
		mtcp->Send(outstring);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *outstring);
	}
	else
	{
		FString outstring;
		//FMessagePackage messagepackage;
		messagepackage.MT = MessageType::EXITGAME;
		FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
		Uentryuicpp::mtcp->Send(outstring);
		UMyBlueprintFunctionLibrary::CLogtofile(FString("OnGameEndevent.Broadcast();"));
		Uentryuicpp::mtcp->exitthread = true;
		connected = false;
		GetWorld()->GetTimerManager().SetTimer(th,this,&Uentryuicpp::Onpressed_mButtonItem,1,false,1);
		mtcp = new TcpClientv();
	}
}
void Uentryuicpp::Onpressed_mButtonItem1()
{
	FMessagePackage mp(MessageType::MATCH, FString("hi"));
	LevelShouldBeLoaded = "/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap";
	if (!connected)
	{
		FString outstring;
		messagepackage.MT = MessageType::MATCH;
		messagepackage.PayLoad = LevelShouldBeLoaded;
		FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
		connected = mtcp->Connecttoserver(192, 168, 1, 240, 8001);
		mtcp->OnTcpClientReceiveddata.AddDynamic(this, &Uentryuicpp::OnTcpResponse);
		mtcp->Send(outstring);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *outstring);
	}
	else
	{
		FString outstring;
		//FMessagePackage messagepackage;
		messagepackage.MT = MessageType::EXITGAME;
		FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
		Uentryuicpp::mtcp->Send(outstring);
		UMyBlueprintFunctionLibrary::CLogtofile(FString("OnGameEndevent.Broadcast();"));
		Uentryuicpp::mtcp->exitthread = true;
		connected = false;
		GetWorld()->GetTimerManager().SetTimer(th, this, &Uentryuicpp::Onpressed_mButtonItem1, 1, false, 1);
		mtcp = new TcpClientv();
	}
	//FString outstring;
	//messagepackage.MT = MessageType::EXITGAME;
	//FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	//mtcp->Send(outstring);
}
void Uentryuicpp::OnTcpResponse(const TArray<uint8>&p, const FString & str)
{
	GEngine->AddOnScreenDebugMessage(-1,15.0f, FColor::Yellow, *str);
	FMessagePackage mp;
	FJsonObjectConverter::JsonObjectStringToUStruct<FMessagePackage>(str, &mp, 0, 0);
	if (mp.MT == MessageType::EntryMAP)
	{
		FString pld = mp.PayLoad;
	
	    FString param = FString::Printf(TEXT("?%s?%s"), *LevelShouldBeLoaded, TEXT("hiparam2"));
		pld.Append(param);
		UGameplayStatics::OpenLevel(GetWorld(),*pld);
		//UGameplayStatics::OpenLevel(GetWorld(), "192.168.1.240:7788");
	}
	//Uentryuicpp::mtcp = nullptr;
	//FString outstring;
	//messagepackage.MT = MessageType::EntryMAPOK;
	//FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	//mtcp->Send(outstring);
}