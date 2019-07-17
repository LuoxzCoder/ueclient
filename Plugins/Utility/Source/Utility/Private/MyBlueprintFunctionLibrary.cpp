﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBlueprintFunctionLibrary.h"
#include "Runtime/Core/Public/HAL/PlatformFilemanager.h"
#include "Runtime/ImageWrapper/Public/IImageWrapperModule.h"
#include "Runtime/Core/Public/Modules/ModuleManager.h"
#include "Runtime/ImageWrapper/Public/IImageWrapper.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/Core/Public/HAL/FileManager.h"
#include "Engine.h"
#include "Runtime/Core/Public/Misc/DateTime.h"
#include "Runtime/Core/Public/Misc/CoreDelegates.h"
#include "Runtime/Core/Public/Misc/SecureHash.h"
#include "Runtime/Core/Public/HAL/UnrealMemory.h"
TArray<FString> UMyBlueprintFunctionLibrary::MountedPakList;
TArray<Fonge> UMyBlueprintFunctionLibrary::OnGameInitevent;
TArray<Fonge> UMyBlueprintFunctionLibrary::OnGameexit;
void UMyBlueprintFunctionLibrary::readstringfromfile(FString filepath, FString & content)
{
	FFileHelper::LoadFileToString(content,*filepath);
}
void UMyBlueprintFunctionLibrary::readdatafromfile(FString filepath, TArray<uint8> & content)
{
	FFileHelper::LoadFileToArray(content,*filepath);
}
bool UMyBlueprintFunctionLibrary::FileMd5isequalSpecificMd5(FString filepath, FString SpecificMd5)
{
	TArray<uint8> content;
	readdatafromfile(filepath, content);
	FString md51 = FMD5::HashBytes(&content[0], content.Num());
	if (md51.Equals(SpecificMd5,ESearchCase::IgnoreCase))
	{
		return true;
	}
	return false;
}
void UMyBlueprintFunctionLibrary::writedatatofile(FString filepath, const TArray<uint8> & content)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	//PlatformFile.CreateDirectory(*filepath);
	FString FileContent = TEXT("This is a line of text to put in the file.\n");
	FFileHelper::SaveStringToFile(FileContent, *filepath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);

	IFileHandle* FileHandle = PlatformFile.OpenWrite(*filepath);
	if (FileHandle)
	{
		uint8* ByteBuffer = (uint8*)&content[0];
		//int32* IntPointer = &MyInteger;
		//uint8* ByteBuffer = reinterpret_cast<uint8*>(IntPointer);

		// Write the bytes to the file
		FileHandle->Write(ByteBuffer, content.Num());

		// Close the file again
		delete FileHandle;
	}
}
bool UMyBlueprintFunctionLibrary::Mount(FString PakFileName)
{
	if (MountedPakList.Contains(PakFileName))
	{
		return false;
	}
	int PakIndex = 0;
	int PakReadOrder = 0;
	FString Contentdir = FPaths::ProjectContentDir();
	Contentdir.Append(PakFileName);
	bool fb = FPaths::FileExists(Contentdir);
	if (fb)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("PakFileName exist"));

	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("PakFileName not exist"));

		return false;
	}
	FString AbsPakPath = FPaths::ConvertRelativePathToFull(Contentdir);
	if (FCoreDelegates::OnMountPak.IsBound())
	{
		auto bSuccess = FCoreDelegates::OnMountPak.Execute(AbsPakPath, PakReadOrder, nullptr);
		if (!bSuccess)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("sandbox"));

			// This can fail because of the sandbox system - which the pak system doesn't understand.
			auto SandboxedPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*AbsPakPath);
			bSuccess = FCoreDelegates::OnMountPak.Execute(SandboxedPath, PakReadOrder, nullptr);
		}
		if (bSuccess)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("mount ok"));

		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("mount fail"));
			return false;

		}
	}
	MountedPakList.Add(PakFileName);
	return true;

}


bool UMyBlueprintFunctionLibrary::UnMount(FString PakFileName)
{
	if (!MountedPakList.Contains(PakFileName))
	{
		return false;
	}
	int PakIndex = 0;
	int PakReadOrder = 0;
	FString Contentdir = FPaths::ProjectContentDir();
	Contentdir.Append(PakFileName);
	bool fb = FPaths::FileExists(Contentdir);
	if (fb)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("PakFileName exist"));

	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("PakFileName not exist"));

		return false;
	}
	FString AbsPakPath = FPaths::ConvertRelativePathToFull(Contentdir);
	if (FCoreDelegates::OnUnmountPak.IsBound())
	{
		auto bSuccess = FCoreDelegates::OnUnmountPak.Execute(AbsPakPath);
		if (!bSuccess)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("unmount sandbox"));

			// This can fail because of the sandbox system - which the pak system doesn't understand.
			auto SandboxedPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*AbsPakPath);
			bSuccess = FCoreDelegates::OnUnmountPak.Execute(SandboxedPath);
		}
		if (bSuccess)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("unmount ok"));

		}
		else
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("unmount fail"));
			return false;

		}
	}
	MountedPakList.Remove(PakFileName);
	return true;
}

void UMyBlueprintFunctionLibrary::RawImageToTexture2D(const TArray<uint8> &RawFileData, class UTexture2D *& out_texture)
{
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	TSharedPtr<IImageWrapper> ImageWrappr = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);//mind the postfix of the source file
	if (ImageWrappr.IsValid()&& ImageWrappr->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
	{
		const TArray<uint8>*UncompressedBGRA = NULL;
		if (ImageWrappr->GetRaw(ERGBFormat::BGRA, 8, UncompressedBGRA))
		{
			out_texture = UTexture2D::CreateTransient(ImageWrappr->GetWidth(),ImageWrappr->GetHeight(), PF_B8G8R8A8);
			void* TextureData = (uint8*)out_texture->PlatformData->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
			FMemory::Memcpy(TextureData, UncompressedBGRA->GetData(),UncompressedBGRA->Num());
			out_texture->PlatformData->Mips[0].BulkData.Unlock();
			out_texture->UpdateResource();
		}
	}
}
void UMyBlueprintFunctionLibrary::CLogtofile(FString msg)
{

	FFileHelper::SaveStringToFile(msg+"  :"+FDateTime::UtcNow().ToString()+"\n", *FPaths::ProjectSavedDir().Append("Log.log"), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}
UObject* UMyBlueprintFunctionLibrary::Loadobject(FString path)
{
	UObject * obj = LoadObject<UObject>(nullptr, *path);
	return obj;
}

void UMyBlueprintFunctionLibrary::Ongameinitfunc()
{
	//clear log file content
	FFileHelper::SaveStringToFile(FString("log file") + "  :" + FDateTime::UtcNow().ToString() + "\n", *FPaths::ProjectSavedDir().Append("Log.log"), FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
	for (auto var : OnGameInitevent)//
	{
		var.ExecuteIfBound();
	}
}

void UMyBlueprintFunctionLibrary::OnGameEndefunc()
{
	for (auto var : OnGameexit)
	{
		var.ExecuteIfBound();
	}
}

void UMyBlueprintFunctionLibrary::AddfunctiontoOnGameIniteventArray(TBaseStaticDelegateInstance<TTypeWrapper<void>()>::FFuncPtr InFuncPtr)
{
	Fonge temp;
	temp.BindStatic(InFuncPtr);
	OnGameInitevent.Add(temp);
}

void UMyBlueprintFunctionLibrary::AddfunctiontoOnGameexitArray(TBaseStaticDelegateInstance<TTypeWrapper<void>()>::FFuncPtr InFuncPtr)
{
	Fonge temp;
	temp.BindStatic(InFuncPtr);
	OnGameexit.Add(temp);
}

