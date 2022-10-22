// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
public class GameFrameEditor : ModuleRules
{
	public GameFrameEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		PrivateDependencyModuleNames.AddRange(
		new string[]
		{			
					"Projects",
					"InputCore",
					"UnrealEd",
					"LevelEditor",
					"CoreUObject",
					"Engine",
					"Slate",
					"SlateCore",
					"EditorStyle",
					"ToolMenus",
					"GameFrame",
					"AnimGraph",
					"BlueprintGraph",
		}
		);
		PublicIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Public") } );
        PrivateIncludePaths.AddRange(new string[] { Path.Combine(ModuleDirectory, "Private") } );
	}
}
