// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UMG.h"
#include "Blueprint/UserWidget.h"
#include "entryuicpp.generated.h"
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class MessageType : uint8
{
	SENDEND,
	SINGUP,
	LOGIN,
	MATCH,
	EntryMAP,
	EntryMAPOK,
	EXITGAME,
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
UCLASS()
class INFINITELIFE1_0_API Uentryuicpp : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY()
	TArray<UObject*> ObjectsArray;
	static bool connected;
	FMessagePackage messagepackage;
	FTimerHandle th;
public:
	static class TcpClientv * mtcp;
	static FString LevelShouldBeLoaded;
	static void clientexit();
	static void clientexit1();
public:
	virtual void NativePreConstruct()override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
public:
	Uentryuicpp(const FObjectInitializer& ObjectInitializer);
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* mButtonItem;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* mButtonItem1;
private:
	UFUNCTION()
		void Onpressed_mButtonItem();
	UFUNCTION()
		void Onpressed_mButtonItem1();
	UFUNCTION()
		void OnTcpResponse(const TArray<uint8>&p, const FString & str);
	UFUNCTION()
		void OnHttpResponse_completed(const FString& Responsestring, const TArray<uint8>& Responsecontent, UObject* extra);
};
