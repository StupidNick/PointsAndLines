#include "GameModes/LAP_GameHUD.h"

#include "Actors/LAP_BaseLevelManager.h"
#include "Blueprint/UserWidget.h"
#include "UI/GameWD/LAP_GameOverWindowWD.h"
#include "UI/GameWD/LAP_MainHUD_WD.h"
#include "UI/MenusWD/LAP_LevelsMenuWD.h"
#include "UI/MenusWD/LAP_MainMenuWD.h"
#include "UI/MenusWD/LAP_SettingsMenuWD.h"


void ALAP_GameHUD::BeginPlay()
{
	Super::BeginPlay();

	CustomPlayerController = Cast<ALAP_PlayerController>(GetOwningPlayerController());
}

void ALAP_GameHUD::CreateMainMenuWD()
{
	if (MainMenuClass && !MainMenu)
	{
		MainMenu = CreateWidget<ULAP_MainMenuWD>(GetWorld(), MainMenuClass);
		MainMenu->AddToViewport();
		MainMenu->InitializeMainMenu(this);
	}
}


void ALAP_GameHUD::RemoveMainMenuWD()
{
	if (!IsValid(MainMenu)) return;
	
	MainMenu->RemoveFromParent();
	MainMenu = nullptr;
}


void ALAP_GameHUD::CreatePauseMenuWD()
{
	if (PauseMenuClass && !PauseMenu)
	{
		PauseMenu = CreateWidget<ULAP_PauseMenu>(GetWorld(), PauseMenuClass);
		PauseMenu->AddToViewport();
		PauseMenu->InitializePauseMenu(this);
	}
}


void ALAP_GameHUD::RemovePauseMenuWD()
{
	if (!IsValid(PauseMenu)) return;
	
	PauseMenu->RemoveFromParent();
	PauseMenu = nullptr;
}


void ALAP_GameHUD::CreateLevelsMenuWD()
{
	if (LevelsMenuClass && !LevelsMenu)
	{
		LevelsMenu = CreateWidget<ULAP_LevelsMenuWD>(GetWorld(), LevelsMenuClass);
		LevelsMenu->AddToViewport();
		LevelsMenu->InitializeLevelsMenu(this);
	}
}


void ALAP_GameHUD::RemoveLevelsMenuWD()
{
	if (!IsValid(LevelsMenu)) return;
	
	LevelsMenu->RemoveFromParent();
	LevelsMenu = nullptr;
}


void ALAP_GameHUD::CreateSettingsMenuWD()
{
	if (SettingsMenuClass && !SettingsMenu)
	{
		SettingsMenu = CreateWidget<ULAP_SettingsMenuWD>(GetWorld(), SettingsMenuClass);
		SettingsMenu->AddToViewport();
		SettingsMenu->InitializeSettingMenu(this);
	}
}


void ALAP_GameHUD::RemoveSettingsMenuWD()
{
	if (!IsValid(SettingsMenu)) return;
	
	SettingsMenu->RemoveFromParent();
	SettingsMenu = nullptr;
}


void ALAP_GameHUD::CreateConfirmWindowWD(FText InConfirmText)
{
	if (ConfirmWindowClass && !ConfirmWindow)
	{
		ConfirmWindow = CreateWidget<ULAP_ConfirmationWindowWD>(GetWorld(), ConfirmWindowClass);
		ConfirmWindow->AddToViewport();
		ConfirmWindow->InitializeConfirmationWindowWD(this, InConfirmText);
	}
}


void ALAP_GameHUD::RemoveConfirmWindowWD()
{
	if (!IsValid(ConfirmWindow)) return;
	
	ConfirmWindow->RemoveFromParent();
	ConfirmWindow = nullptr;
}


void ALAP_GameHUD::CreateMainHUD_WD(int32 InLevelID)
{
	if (MainHUD_WD_Class && !MainHUD_WD)
	{
		MainHUD_WD = CreateWidget<ULAP_MainHUD_WD>(GetWorld(), MainHUD_WD_Class);
		MainHUD_WD->AddToViewport();
		MainHUD_WD->InitializeMainHUD_WD(this);
	}
}


void ALAP_GameHUD::RemoveMainHUD_WD()
{
	if (!IsValid(MainHUD_WD)) return;
	
	MainHUD_WD->RemoveFromParent();
	MainHUD_WD = nullptr;
}


void ALAP_GameHUD::CreateGameOverWindowWD(bool bInPlayerIsWin)
{
	if (GameOverWindowClass && !GameOverWindow)
	{
		GameOverWindow = CreateWidget<ULAP_GameOverWindowWD>(GetWorld(), GameOverWindowClass);
		GameOverWindow->AddToViewport();
		GameOverWindow->InitializeGameOverWindowWD(this, bInPlayerIsWin);
	}
}

void ALAP_GameHUD::RemoveGameOverWindowWD()
{
	if (!IsValid(GameOverWindow)) return;
	
	GameOverWindow->RemoveFromParent();
	GameOverWindow = nullptr;
}


void ALAP_GameHUD::RemoveAllWidgets()
{
	RemoveGameOverWindowWD();
	RemoveMainHUD_WD();
	RemoveConfirmWindowWD();
	RemoveSettingsMenuWD();
	RemoveLevelsMenuWD();
	RemoveMainMenuWD();
}
