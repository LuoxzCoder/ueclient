// Fill out your copyright notice in the Description page of Project Settings.


#include "TcpGameInstance.h"
#include "TcpCommunicatorv1.h"
#include "UTcpCommunicatorv2.h"


UTcpGameInstance::UTcpGameInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}
UTcpCommunicatorv1 * UTcpGameInstance::GetSignUpLoginClient()
{
	if (SignUpLoginClient == nullptr)
	{
		SignUpLoginClient = NewObject<UTcpCommunicatorv1>();
		SignUpLoginClient->world = GetWorld();
	}
	return SignUpLoginClient;
}
UUTcpCommunicatorv2 * UTcpGameInstance::GetMatchClient()
{
	if (MatchClient == nullptr)
	{
		MatchClient = NewObject<UUTcpCommunicatorv2>();
		MatchClient->world = GetWorld();
	}
	return MatchClient;
}