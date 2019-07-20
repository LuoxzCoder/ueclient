// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUIcpp.h"
#include "TcpClientv.h"
#include "JsonUtilities.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Json.h"
#include "MyBlueprintFunctionLibrary.h"
class TcpClientv* ULoginUIcpp::mtcp = nullptr;
void ULoginUIcpp::clientexit()
{

	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::EXITGAME;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	ULoginUIcpp::mtcp->Send(outstring);
	FPlatformProcess::Sleep(0.03);
	ULoginUIcpp::mtcp->exitthread = true;

}
void ULoginUIcpp::NativePreConstruct()
{
	if (mButtonItemSingUp)
	{
		mButtonItemSingUp->OnClicked.AddDynamic(this, &ULoginUIcpp::Onpressed_mButtonItemSingUp);
	}
	if (mButtonItemLogin)
	{
		mButtonItemLogin->OnClicked.AddDynamic(this, &ULoginUIcpp::Onpressed_mButtonItemLogin);
	}
}
void ULoginUIcpp::NativeConstruct()
{
	if (mtcp == nullptr)
	{
		mtcp = new TcpClientv();
		isconnected = mtcp->Connecttoserver(192, 168, 1, 240, 8002);
		mtcp->OnTcpClientReceiveddata.AddDynamic(this, &ULoginUIcpp::OnTcpResponse);
		if (isconnected)
		{

		}
		UMyBlueprintFunctionLibrary::AddfunctiontoOnGameexitArray(&ULoginUIcpp::clientexit);
	}
	GetWorld()->GetTimerManager().SetTimer(th, this, &ULoginUIcpp::thwork, 0.5, true, 1);

}
void ULoginUIcpp::Onpressed_mButtonItemSingUp()
{
	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::SINGUP;
	FString username = musername->GetText().ToString();
	FString password = mpassword->GetText().ToString();
	if (username.Equals(""))
	{
		return;
	}
	messagepackage.PayLoad = username+"?"+password;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	ULoginUIcpp::mtcp->Send(outstring);
}
void ULoginUIcpp::Onpressed_mButtonItemLogin()
{
	FString outstring;
	FMessagePackage messagepackage;
	messagepackage.MT = MessageType::LOGIN;
	FString username = musername->GetText().ToString();
	FString password = mpassword->GetText().ToString();
	if (username.Equals(""))
	{
		return;
	}
	messagepackage.PayLoad = username + "?" + password;
	FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	ULoginUIcpp::mtcp->Send(outstring);
	//UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonExampleMap");

}
void ULoginUIcpp::OnTcpResponse(const TArray<uint8>&p, const FString & str)
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
	if (mp.MT == MessageType::LOGIN)
	{
		FString pld = mp.PayLoad;
		if (pld.Equals("succeed"))
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("login succeed"));
			OnTcpResponsestate = 1;
			//WidgetBlueprint'/Game/FirstPersonBP/Maps/entryui.entryui'
			//UClass* uwp = (UClass*)LoadClass<UObject>(NULL, TEXT("WidgetBlueprint'/Game/FirstPersonBP/Maps/entryui.entryui_C'"));
		   // UUserWidget *widget = CreateWidget<UUserWidget>(GetWorld(), uwp);
			//widget->AddToViewport();		
			//World'/Game/FirstPersonBP/Maps/FirstPersonExampleMap.FirstPersonExampleMap'
			//UGameplayStatics::OpenLevel(GetWorld(), "/Game/FirstPersonBP/Maps/FirstPersonExampleMap");
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("login failed"));

		}

	}
	//Uentryuicpp::mtcp = nullptr;
	//FString outstring;
	//messagepackage.MT = MessageType::EntryMAPOK;
	//FJsonObjectConverter::UStructToJsonObjectString<FMessagePackage>(messagepackage, outstring);
	//mtcp->Send(outstring);
}
void ULoginUIcpp::thwork()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("thwork"));
	if (OnTcpResponsestate == 1)
	{
		UClass* uwp = (UClass*)LoadClass<UObject>(NULL, TEXT("WidgetBlueprint'/Game/FirstPersonBP/Maps/entryui.entryui_C'"));
		UUserWidget *widget = CreateWidget<UUserWidget>(GetWorld(), uwp);
		widget->AddToViewport();	
		this->RemoveFromParent();
		OnTcpResponsestate = 0;
	}

}