// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Runtime/Core/Public/Containers/Array.h"
#include "Runtime/CoreUObject/Public/UObject/Object.h"
#include "MyBlueprintFunctionLibrary.generated.h"
DECLARE_DELEGATE(Fonge);
/**
 * 
 */
UCLASS()
class UTILITY_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	static TArray<FString> MountedPakList;
public:
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static void readstringfromfile(FString filepath, FString & content);
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static void readdatafromfile(FString filepath, TArray<uint8> & content);
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static bool FileMd5isequalSpecificMd5(FString filepath, FString SpecificMd5);
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static void writedatatofile(FString filepath, const TArray<uint8> & content);
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static bool Mount(FString PakFileName);
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static bool UnMount(FString PakFileName);
	static void RawImageToTexture2D(const TArray<uint8> &data,class UTexture2D *& out_texture);
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static void CLogtofile(FString msg);
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static UObject* Loadobject(FString path);
public:
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static void Ongameinitfunc();
	UFUNCTION(BlueprintCallable, Category = "Mybp")
	static void OnGameEndefunc();
	static TArray<Fonge> OnGameexit;
	static TArray<Fonge> OnGameInitevent;
	static void AddfunctiontoOnGameIniteventArray(TBaseStaticDelegateInstance<TTypeWrapper<void>()>::FFuncPtr InFuncPtr);
	static void AddfunctiontoOnGameexitArray(TBaseStaticDelegateInstance<TTypeWrapper<void>()>::FFuncPtr InFuncPtr);
};
