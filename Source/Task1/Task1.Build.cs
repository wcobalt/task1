// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Task1 : ModuleRules
{
	public Task1(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory + "/Public");
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "UMG",
			"GameplayAbilities", "GameplayTasks", "GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
