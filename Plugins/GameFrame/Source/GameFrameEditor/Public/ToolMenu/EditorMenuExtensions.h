#pragma once

class FEditorMenuExtensions
{
public:
	static void ExtendMenus();
	static void ExtendToolbars();
	static void ExtendContexMenu();
	static void ExtendContentBrowserContextMenu();
	static void GenerateMenuContent(FMenuBuilder& MenuBuilder);
};

struct FInteractiveReadTableInfo
{
	
public:
		int32 id;
		FString tableName;
		FString resourcePath;
		FString model;
		FString interactiveType;
};
