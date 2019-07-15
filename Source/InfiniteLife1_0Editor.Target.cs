// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class InfiniteLife1_0EditorTarget : TargetRules
{
	public InfiniteLife1_0EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "InfiniteLife1_0" } );
	}
}
