// Fill out your copyright notice in the Description page of Project Settings.


#include "mainui_cpp.h"
#include "UTcpCommunicatorv2.h"
#include "TcpGameInstance.h"
#include "ArchiveToolFunctionLibrary.h"
void Umainui_cpp::NativePreConstruct()
{
	if (mButtonItem)
	{
		mButtonItem->OnClicked.AddDynamic(this, &Umainui_cpp::Onpressed_mButtonItem);
	}
	UGameInstance* gameinstance = GetWorld()->GetGameInstance();
	UTcpGameInstance* tcpgameinstance = Cast<UTcpGameInstance>(gameinstance);
	check(tcpgameinstance);
	tcpclient = tcpgameinstance->GetSignUpLoginClient();
	check(tcpclient);
	//tcpclient->OnLogInSucceed.AddDynamic(this, &ULoginUIcpp::ChangeUi);
	tcpclient->ConnectServer();
}
void Umainui_cpp::NativeConstruct()
{

}
void Umainui_cpp::Onpressed_mButtonItem()
{
	FString str = UArchiveToolFunctionLibrary::ArchiveActorTransformbyTag(this, nullptr, "archive");

	tcpclient->SendMapActorInforfile(str);
}