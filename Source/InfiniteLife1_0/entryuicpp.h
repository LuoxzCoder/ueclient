// Fill out your copyright notice in the Description page of Project Settings.
//match server ok
#pragma once

#include "CoreMinimal.h"
#include "UMG.h"
#include "TcpCommunicatorv1.h"
#include "Blueprint/UserWidget.h"
#include "ArchiveToolFunctionLibrary.h"
#include "entryuicpp.generated.h"
/**
 * 
 */
UCLASS()
class INFINITELIFE1_0_API Uentryuicpp : public UUserWidget
{
	GENERATED_BODY()
	class UUTcpCommunicatorv2* matchclient;
	FString LevelShouldBeLoaded;



	//bool isfilegoing=false;
	//FString st;
	//FArchiveList archivelist;
	//UPROPERTY()
	//TArray<UObject*> ObjectsArray;
	//static bool connected;
	//FMessagePackage messagepackage;
	//FTimerHandle th;
public:
	//static class TcpClientv * mtcp;
	//static void clientexit();
	//static void clientexit1();
	//static void clientexitv1(const TArray<uint8>&,const FString&);
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
};
