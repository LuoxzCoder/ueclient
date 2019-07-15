// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class InfiniteLife1_0Target : TargetRules
{
	public InfiniteLife1_0Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "InfiniteLife1_0" } );
	}
}
