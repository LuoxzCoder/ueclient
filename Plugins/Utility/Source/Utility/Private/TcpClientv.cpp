﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TcpClientv.h"
#include "Runtime/Sockets/Public/SocketSubsystem.h"
#include "Runtime/Networking/Public/Interfaces/IPv4/IPv4Address.h"
#include "Runtime/Sockets/Public/IPAddress.h"
#include "Runtime/Sockets/Public/Sockets.h"
#include "Engine.h"
#include "MyBlueprintFunctionLibrary.h"
TcpClientv::TcpClientv()
{
	Socket = ISocketSubsystem::Get()->CreateSocket(NAME_Stream, TEXT("default"), false);
}

TcpClientv::~TcpClientv()
{
	UMyBlueprintFunctionLibrary::CLogtofile(FString("~TcpClientv()"));
}

bool TcpClientv::Connecttoserver(uint8 a, uint8 b, uint8 c, uint8 d, uint32 port)
{
	FIPv4Address ip(a, b, c, d);

	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get()->CreateInternetAddr();
	addr->SetIp(ip.Value);
	addr->SetPort(port);
	bool connected = Socket->Connect(*addr);
	if (connected)
	{
		UMyBlueprintFunctionLibrary::CLogtofile(FString("connected ok"));
		Async<void>(EAsyncExecution::ThreadPool, [=]() {ReceiveWork(); }, nullptr);
	}
	return connected;
}

bool TcpClientv::Send(FString & serialized)
{
	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	int32 size = FCString::Strlen(serializedChar);
	int32 sent = 0;
	bool successful = Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
	return successful;
}

bool TcpClientv::Send(const uint8 * content, const int32 & size)
{
	int32 sent = 0;
	bool successful = Socket->Send(content, size, sent);
	return successful;
}

void TcpClientv::ReceiveWork()
{
	UMyBlueprintFunctionLibrary::CLogtofile(FString("ReceiveWork() ok"));

	while (true)
	{
		if (exitthread)
		{
			UMyBlueprintFunctionLibrary::CLogtofile(FString("exitthread"));
			Socket->Close();
			delete this;
			break;
		}
		if (Socket == nullptr)
		{
			UMyBlueprintFunctionLibrary::CLogtofile(FString("Socket == nullptr"));
			delete this;
			break;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("UTcpClient threadworker"));
		FPlatformProcess::Sleep(0.03);
		ESocketConnectionState state = Socket->GetConnectionState();
		if (state != ESocketConnectionState::SCS_Connected)
		{
			UMyBlueprintFunctionLibrary::CLogtofile(FString("SCS_ConnectionError"));
			Socket->Close();
			delete this;
			break;
		}
	
		bool b = false;
		if (state == ESocketConnectionState::SCS_Connected)
		{
			b = Socket->HasPendingData(datasize);
		}
		int32 bytes;
		if (b)
		{
			UMyBlueprintFunctionLibrary::CLogtofile(FString(" Socket->HasPendingData(datasize) is ture"));
			// u need to ensure single package not bigger than 65536 byte
			// and the time gap between two packages is needed and at least 30ms 
			datareceive.Empty();
			datareceive.AddUninitialized(datasize);
			//Socket->Recv(&datareceive[(counter++) * 65536], datasize, bytes, ESocketReceiveFlags::None);
			UMyBlueprintFunctionLibrary::CLogtofile(FString(UTF8_TO_TCHAR(&datareceive[0])).Left(datareceive.Num()));
			Socket->Recv(&datareceive[0], datasize, bytes, ESocketReceiveFlags::None);
			UMyBlueprintFunctionLibrary::CLogtofile(FString(UTF8_TO_TCHAR(&datareceive[0])).Left(datareceive.Num()));
		    OnTcpClientReceiveddata.Broadcast(datareceive, FString(UTF8_TO_TCHAR(&datareceive[0])).Left(datareceive.Num()));
		}
		//else
		//{
		//	UMyBlueprintFunctionLibrary::CLogtofile(FString("if (datareceive.Num() > 0) before"));

		//	if (datareceive.Num() > 0)
		//	{             
		//		UMyBlueprintFunctionLibrary::CLogtofile(FString(UTF8_TO_TCHAR(&datareceive[0])).Left(datareceive.Num()));
		//	                                             //the string may should not be trust
		//		OnTcpClientReceiveddata.Broadcast(datareceive, FString(UTF8_TO_TCHAR(&datareceive[0])).Left(datareceive.Num()));
		//		datareceive.Empty();	
		//      counter = 0;
		//	}
		//	UMyBlueprintFunctionLibrary::CLogtofile(FString("if (datareceive.Num() > 0) after"));

		//}
	}
}