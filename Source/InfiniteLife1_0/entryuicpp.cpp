// Fill out your copyright notice in the Description page of Project Settings.


#include "entryuicpp.h"
#include "TcpClientv.h"
#include "JsonUtilities.h"
#include "Json.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "MyBlueprintFunctionLibrary.h"
#include "HttpServicev.h"


#include "UTcpCommunicatorv2.h"
#include "TcpGameInstance.h"
Uentryuicpp::Uentryuicpp(const FObjectInitializer & ObjectInitializer) : Super(ObjectInitializer)
{

}
//void Uentryuicpp::clientexit()
//{
//
//	FString outstring;
//	FMessagePackage messagepackage;
//	messagepackage.MT = MessageType::EXITGAME;
//	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
//	Uentryuicpp::mtcp->Send(outstring);
//	FPlatformProcess::Sleep(0.03);
//	//Uentryuicpp::mtcp->Send((uint8*)outstring.GetCharArray().GetData(),outstring.Len()*2);
//	UMyBlueprintFunctionLibrary::CLogtofile(FString("OnGameEndevent.Broadcast();"));
//	Uentryuicpp::mtcp->exitthread = true;
//
//}
//void Uentryuicpp::clientexit1()
//{
//	UMyBlueprintFunctionLibrary::CLogtofile(FString("Uentryuicpp::clientexit1()"));
//
//}
//void Uentryuicpp::clientexitv1(const TArray<uint8>& arr, const FString& str)
//{
//	
//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *str);
//
//}
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
	UGameInstance* gameinstance = GetWorld()->GetGameInstance();
	UTcpGameInstance* tcpgameinstance = Cast<UTcpGameInstance>(gameinstance);
	check(tcpgameinstance);
	matchclient = tcpgameinstance->GetMatchClient();
	check(matchclient);
	matchclient->init();
	//FString teststr = "hithisastring";
	//FString t1 = teststr.RightChop(10);
	//FString t2 = teststr.RightChop(13);
	//FString t3 = teststr.RightChop(15);
	//if (mtcp == nullptr)
	//{
	//	mtcp = new TcpClientv();

	//	UMyBlueprintFunctionLibrary::AddfunctiontoOnGameexitArray(&Uentryuicpp::clientexit);
	//	UMyBlueprintFunctionLibrary::AddfunctiontoOnGameIniteventwithparameterArray(&Uentryuicpp::clientexitv1);
	//	//UMyBlueprintFunctionLibrary::AddfunctiontoOnGameexitArray(&Uentryuicpp::clientexit1);
	//}



	//FString outstring;
	//connected = mtcp->Connecttoserver(192, 168, 1, 240, 8001);
	//mtcp->OnTcpClientReceiveddata.AddDynamic(this, &Uentryuicpp::OnTcpResponse);

	//messagepackage.MT = MessageType::FILE;
	//FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	//Uentryuicpp::mtcp->Send(outstring);
	//FPlatformProcess::Sleep(0.05);
	//FString strpersistent;
	//FString str= strpersistent = UArchiveToolFunctionLibrary::ArchiveActorTransformbyTag(this, nullptr, "archive");
	//do {
	//	FString file_str = str.Len() > 32768 ? str.Left(32768) : str;//string should be encode by unicode
	//	Uentryuicpp::mtcp->Send(file_str);
	//	str = str.RightChop(32768);
	//	while (!isfilegoing)
	//	{
	//		FPlatformProcess::Sleep(0.01);
	//	}
	//	isfilegoing = false;
	//} while (!str.IsEmpty());
	//messagepackage.MT = MessageType::FILEEND;
	//FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	//Uentryuicpp::mtcp->Send(outstring);


	//uint8*outarray;
	//TArray<uint8> uarray;
	//int64 size;
	//UMyBlueprintFunctionLibrary::FStringtoUTF16(strpersistent, outarray, size);

	//FString path = "e://write.log";
	//UMyBlueprintFunctionLibrary::writedatatofile(path, outarray, size);

	//UMyBlueprintFunctionLibrary::readdatafromfile(path, uarray);

	//st = UMyBlueprintFunctionLibrary::UTF16toFString(uarray, uarray.Num());
	//FJsonObjectConverter::JsonObjectStringToUStruct<FArchiveList>(st, &archivelist, 0, 0);
	//FString n = archivelist.name;

	//http->OnHttpResponseComplete.AddDynamic(this, &Uentryuicpp::OnHttpResponse_completed);
	//http->HttpGet("http://192.168.1.240/file/file.rar");
}
//void Uentryuicpp::OnHttpResponse_completed(const FString& Responsestring, const TArray<uint8>& Responsecontent, UObject* extra)
//{
//	UMyBlueprintFunctionLibrary::writedatatofile(FString("d:/ue.rar"), Responsecontent);
//}
void Uentryuicpp::NativeTick(const FGeometry & MyGeometry, float InDeltaTime)
{
	
}

void Uentryuicpp::Onpressed_mButtonItem()
{
	LevelShouldBeLoaded = "/Game/FirstPersonBP/Maps/FirstPersonExampleMap";
	matchclient->mapname = LevelShouldBeLoaded;
	matchclient->GetMapArchiveInfor(LevelShouldBeLoaded);
	//loading special effects



	//while (!matchclient->filereceiveok)
	//{
	//	FPlatformProcess::Sleep(0.03);
	//}

	//matchclient->OpenServermap(LevelShouldBeLoaded);
	//FMessagePackage mp(MessageType::MATCH,FString("hi"));
	//LevelShouldBeLoaded = "/Game/FirstPersonBP/Maps/FirstPersonExampleMap";
	//if (!connected)
	//{
	//	FString outstring;
	//	messagepackage.MT = MessageType::MATCH;
	//	messagepackage.PayLoad = LevelShouldBeLoaded;
	//	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	//	connected = mtcp->Connecttoserver(192, 168, 1, 240, 8001);
	//	mtcp->OnTcpClientReceiveddata.AddDynamic(this, &Uentryuicpp::OnTcpResponse);
	//	mtcp->Send(outstring);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *outstring);
	//}
	//else
	//{
	//	FString outstring;
	//	//FMessagePackage messagepackage;
	//	messagepackage.MT = MessageType::EXITGAME;
	//	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	//	Uentryuicpp::mtcp->Send(outstring);
	//	UMyBlueprintFunctionLibrary::CLogtofile(FString("OnGameEndevent.Broadcast();"));
	//	Uentryuicpp::mtcp->exitthread = true;
	//	connected = false;
	//	GetWorld()->GetTimerManager().SetTimer(th,this,&Uentryuicpp::Onpressed_mButtonItem,1,false,1);
	//	mtcp = new TcpClientv();
	//}
}
void Uentryuicpp::Onpressed_mButtonItem1()
{
	LevelShouldBeLoaded = "/Game/ThirdPersonBP/Maps/ThirdPersonExampleMap";
	matchclient->mapname = LevelShouldBeLoaded;
	matchclient->GetMapArchiveInfor(LevelShouldBeLoaded);
	//loading special effects


	//FMessagePackage mp(MessageType::MATCH, FString("hi"));
	//if (!connected)
	//{
	//	FString outstring;
	//	messagepackage.MT = MessageType::MATCH;
	//	messagepackage.PayLoad = LevelShouldBeLoaded;
	//	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	//	connected = mtcp->Connecttoserver(192, 168, 1, 240, 8001);
	//	mtcp->OnTcpClientReceiveddata.AddDynamic(this, &Uentryuicpp::OnTcpResponse);
	//	mtcp->Send(outstring);
	//	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *outstring);
	//}
	//else
	//{
	//	FString outstring;
	//	//FMessagePackage messagepackage;
	//	messagepackage.MT = MessageType::EXITGAME;
	//	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	//	Uentryuicpp::mtcp->Send(outstring);
	//	UMyBlueprintFunctionLibrary::CLogtofile(FString("OnGameEndevent.Broadcast();"));
	//	Uentryuicpp::mtcp->exitthread = true;
	//	connected = false;
	//	GetWorld()->GetTimerManager().SetTimer(th, this, &Uentryuicpp::Onpressed_mButtonItem1, 1, false, 1);
	//	mtcp = new TcpClientv();
	//}

}
//void Uentryuicpp::OnTcpResponse(const TArray<uint8>&p, const FString & str)
//{
//	GEngine->AddOnScreenDebugMessage(-1,15.0f, FColor::Yellow, *str);
//	FMessagePackage mp;
//	FJsonObjectConverter::JsonObjectStringToUStruct<FMessagePackage>(str, &mp, 0, 0);
//	if (mp.MT == MessageType::EntryMAP)
//	{
//		FString pld = mp.PayLoad;
//	
//	    FString param = FString::Printf(TEXT("?%s?%s"), *LevelShouldBeLoaded, TEXT("hiparam2"));
//		pld.Append(param);
//		UGameplayStatics::OpenLevel(GetWorld(),*pld);
//		//UGameplayStatics::OpenLevel(GetWorld(), "192.168.1.240:7788");
//	}
//	if (mp.MT == MessageType::FILE)
//	{
//		isfilegoing = true;
//	}
//	//Uentryuicpp::mtcp = nullptr;
//	//FString outstring;
//	//messagepackage.MT = MessageType::EntryMAPOK;
//	//FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
//	//mtcp->Send(outstring);
//}