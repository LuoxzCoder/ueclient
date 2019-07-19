// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "entryuicpp.h"
#include "Blueprint/UserWidget.h"
#include "LoginUIcpp.generated.h"

/**
 * 
 */
UCLASS()
class INFINITELIFE1_0_API ULoginUIcpp : public UUserWidget
{
	GENERATED_BODY()
		bool isconnected = false;
public:
	virtual void NativePreConstruct()override;
	virtual void NativeConstruct() override;
public:
	static class TcpClientv * mtcp;
	static void clientexit();

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* musername;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* mpassword;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* mButtonItemSingUp;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* mButtonItemLogin;
private:
	UFUNCTION()
		void Onpressed_mButtonItemSingUp();
	UFUNCTION()
		void Onpressed_mButtonItemLogin();
	UFUNCTION()
		void OnTcpResponse(const TArray<uint8>&p, const FString & str);
};
