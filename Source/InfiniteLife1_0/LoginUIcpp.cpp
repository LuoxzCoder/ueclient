// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginUIcpp.h"
#include "TcpClientv.h"
#include "JsonUtilities.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Json.h"
#include "MyBlueprintFunctionLibrary.h"

#include "TcpCommunicatorv1.h"
#include "TcpGameInstance.h"


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
	UGameInstance* gameinstance = GetWorld()->GetGameInstance();
	tcpgameinstance = Cast<UTcpGameInstance>(gameinstance);
	check(tcpgameinstance);
	tcpclient = tcpgameinstance->GetSignUpLoginClient();
	check(tcpclient);
	tcpclient->OnLogInSucceed.AddDynamic(this, &ULoginUIcpp::ChangeUi);
	tcpclient->ConnectServer();
}
void ULoginUIcpp::ChangeUi()
{
	UClass* uwp = (UClass*)LoadClass<UObject>(NULL, TEXT("WidgetBlueprint'/Game/FirstPersonBP/Maps/entryui.entryui_C'"));
	UUserWidget *widget = CreateWidget<UUserWidget>(GetWorld(), uwp);
	widget->AddToViewport();	
	this->RemoveFromParent();
}
void ULoginUIcpp::NativeConstruct()
{
}
void ULoginUIcpp::Onpressed_mButtonItemSingUp()
{

	FString username = musername->GetText().ToString();
	FString password = mpassword->GetText().ToString();

	tcpclient->SignUp(username, password);

}
void ULoginUIcpp::Onpressed_mButtonItemLogin()
{

	FString username = musername->GetText().ToString();
	FString password = mpassword->GetText().ToString();

	tcpclient->LogIn(username, password);
	check(tcpgameinstance);
	tcpgameinstance->username = username;
	tcpgameinstance->password = password;
}