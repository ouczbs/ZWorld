// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.IO;
public class Protobuf : ModuleRules
{
	public Protobuf(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core" });

		PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject" , "Engine"});

        ShadowVariableWarningLevel = WarningLevel.Warning;
        PublicIncludePaths.AddRange(
            new string[] {
                 Path.Combine(ModuleDirectory, "Public"),
                 Path.Combine(ModuleDirectory, "include"),
                // ... add public include paths required here ...
            }
        );
        PrivateIncludePaths.AddRange(
            new string[] {
                Path.Combine(ModuleDirectory, "lib"),
                Path.Combine(ModuleDirectory, "Private"),
            }
        );
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "lib" , "libprotobuf.lib"));
	}
}
