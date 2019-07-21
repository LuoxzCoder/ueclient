// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "UObject/NoExportTypes.h"
#include "TcpCommunicatorv1.generated.h"
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class MessageType : uint8
{
	SENDEND,
	SINGUP,
	LOGIN,
	MATCH,
	SAVEMAPACTORINFOR,
	EntryMAP,
	EntryMAPOK,
	EXITGAME,
	FILE,
	FILEEND,
};
USTRUCT()
struct FMessagePackage {
	GENERATED_BODY()
		UPROPERTY()
		MessageType MT;
	UPROPERTY()
		FString PayLoad;
	FMessagePackage()
	{
		MT = MessageType::LOGIN;
		PayLoad = "";
	}
	FMessagePackage(MessageType mMT, FString mPayLoad)
	{
		MT = mMT;
		PayLoad = mPayLoad;
	}
};
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLogInsucceed);

UCLASS()
class TCPSCENV1_API UTcpCommunicatorv1 : public UObject
{
	GENERATED_BODY()
	UTcpCommunicatorv1(const FObjectInitializer& ObjectInitializer);
	static class TcpClientv * mtcp;
	static void clientexit();
	FTimerHandle th;
	void thwork();
	bool isfilegoing = false;
	UFUNCTION()
		void OnTcpResponse(const TArray<uint8>&p, const FString & str);
private:
	bool isconnected = false;
	int OnTcpResponsestate = 0;
	void Sendfile(FString &filecontent);
public:
	class UWorld* world;
	bool ConnectServer();
	void SignUp(FString username, FString password);
	void LogIn(FString username, FString password);
	void SendMapActorInforfile(FString &filecontent);

	UPROPERTY()
	FOnLogInsucceed OnLogInSucceed;
};
