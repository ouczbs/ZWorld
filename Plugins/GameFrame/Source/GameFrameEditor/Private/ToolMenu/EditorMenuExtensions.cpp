// Copyright

#include "ToolMenu/EditorMenuExtensions.h"
#include "ToolMenu/EditorMenuActions.h"
#include "ToolMenus.h"

#define LOCTEXT_NAMESPACE "FEditorMenuExtensions"
void FEditorMenuExtensions::GenerateMenuContent(FMenuBuilder& MenuBuilder)
{
	{
		MenuBuilder.AddMenuEntry(
			FText::FromString("Open Main Level"),
			FText::FromString("Open Main Level"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateStatic(&FEditorMenuActions::OpenMainLevel)),
			NAME_None,
			EUserInterfaceActionType::Button
		);
	}
	{
		MenuBuilder.BeginSection("Lua Tools", FText::FromString("Lua Tools"));
		MenuBuilder.AddMenuEntry(
			FText::FromString("Gen Blueprint Type"),
			FText::FromString("Gen Blueprint Type"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateStatic(&FEditorMenuActions::AutoGenBlueprintTypeRefForLua)),
			NAME_None,
			EUserInterfaceActionType::Button
		);
		MenuBuilder.AddMenuEntry(
			FText::FromString("Gen Pbc"),
			FText::FromString("Gen Pbc"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateStatic(&FEditorMenuActions::AutoGenPbc)),
			NAME_None,
			EUserInterfaceActionType::Button
		);
		MenuBuilder.AddMenuEntry(
			FText::FromString("Gen LuaModule"),
			FText::FromString("Gen LuaModule"),
			FSlateIcon(),
			FUIAction(FExecuteAction::CreateStatic(&FEditorMenuActions::AutoGenLuaModule)),
			NAME_None,
			EUserInterfaceActionType::Button
		);
		MenuBuilder.EndSection();
	}
}
void FEditorMenuExtensions::ExtendMenus()
{
	FEditorMenuExtensions::ExtendToolbars();
	FEditorMenuExtensions::ExtendContexMenu();
	FEditorMenuExtensions::ExtendContentBrowserContextMenu();
}

void FEditorMenuExtensions::ExtendToolbars()
{
	UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
	{
		FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("WindowLayout");
		{
			// create menu
			Section.AddSubMenu(
				"Game Tools",
				LOCTEXT("Game", "My Game Tools"),
				LOCTEXT("Game_ToolTip", "List Of Game Tools"),
				FNewMenuDelegate::CreateStatic(&FEditorMenuExtensions::GenerateMenuContent),
				false,
				FSlateIcon(FAppStyle::GetAppStyleSetName(), "Game.Tool")
			);
		}
	}
}

void FEditorMenuExtensions::ExtendContexMenu()
{
	
}

void FEditorMenuExtensions::ExtendContentBrowserContextMenu()
{
	
}
#undef LOCTEXT_NAMESPACE