// Fill out your copyright notice in the Description page of Project Settings.


#include "TcpCommunicatorv1.h"
#include "TcpClientv.h"
#include "Engine.h"
#include "JsonUtilities.h"
#include "Json.h"
#include "MyBlueprintFunctionLibrary.h"
class TcpClientv* UTcpCommunicatorv1::mtcp = nullptr;
UTcpCommunicatorv1::UTcpCommunicatorv1(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{//UObject(const FObjectInitializer& ObjectInitializer)

}
void UTcpCommunicatorv1::clientexit()
{

	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::EXITGAME;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	UTcpCommunicatorv1::mtcp->Send(outstring);
	FPlatformProcess::Sleep(0.03);
	UTcpCommunicatorv1::mtcp->exitthread = true;

}
bool UTcpCommunicatorv1::ConnectServer()
{
	if (mtcp == nullptr)
	{
		mtcp = new TcpClientv();
		isconnected = mtcp->Connecttoserver(192, 168, 1, 240, 8002);
		mtcp->OnTcpClientReceiveddata.AddDynamic(this, &UTcpCommunicatorv1::OnTcpResponse);
		if (isconnected)
		{

		}
		UMyBlueprintFunctionLibrary::AddfunctiontoOnGameexitArray(&UTcpCommunicatorv1::clientexit);
		check(world);
		world->GetTimerManager().SetTimer(th, this, &UTcpCommunicatorv1::thwork, 0.5, true, 1);
	}
	return isconnected;
}
void UTcpCommunicatorv1::SignUp(FString username, FString password)
{
	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::SINGUP;
	if (username.Equals(""))
	{
		return;
	}
	messagepackage.PayLoad = username + "?" + password;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	mtcp->Send(outstring);
}
void UTcpCommunicatorv1::LogIn(FString username, FString password)
{
	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::LOGIN;
	if (username.Equals(""))
	{
		return;
	}
	messagepackage.PayLoad = username + "?" + password;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	mtcp->Send(outstring);
}
void UTcpCommunicatorv1::Sendfile(FString &str)
{
	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::FILE;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	mtcp->Send(outstring);
	FPlatformProcess::Sleep(0.05);
	FString strpersistent;
	do {
		FString file_str = str.Len() > 32768 ? str.Left(32768) : str;//string should be encode by unicode
		mtcp->Send(file_str);
		str = str.RightChop(32768);
		while (!isfilegoing)
		{
			FPlatformProcess::Sleep(0.01);
		}
		isfilegoing = false;
	} while (!str.IsEmpty());
	messagepackage.MT = MessageType::FILEEND;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	mtcp->Send(outstring);
	while (!isfilereceiveok)
	{
		FPlatformProcess::Sleep(0.01);
	}
	isfilereceiveok = false;
}
void UTcpCommunicatorv1::SendMapActorInforfile(FString &str)
{
	Sendfile(str);
	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::SAVEMAPACTORINFOR;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	mtcp->Send(outstring);
}
void UTcpCommunicatorv1::OnTcpResponse(const TArray<uint8>& p, const FString & str)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *str);
	FMessagePackage mp;
	FJsonObjectConverter::JsonObjectStringToUStruct<FMessagePackage>(str, &mp, 0, 0);
	if (mp.MT == MessageType::SINGUP)
	{
		FString pld = mp.PayLoad;
		if (pld.Equals("succeed"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("signup succeed"));

		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("signup failed"));

		}
	}
	else if (mp.MT == MessageType::LOGIN)
	{
		FString pld = mp.PayLoad;
		if (pld.Equals("succeed"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("login succeed"));
			OnTcpResponsestate = 1;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("login failed"));

		}

	}
	else if (mp.MT == MessageType::FILE)
	{
		isfilegoing = true;
	}
	else if (mp.MT == MessageType::FILERECEIVEOK)
	{
		isfilereceiveok = true;
	}
}
void UTcpCommunicatorv1::thwork()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("thwork"));
	if (OnTcpResponsestate == 1)
	{
		if (OnLogInSucceed.IsBound())
		{
			OnLogInSucceed.Broadcast();
		}
		OnTcpResponsestate = 0;
	}

}