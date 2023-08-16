#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerControllers/LAP_PlayerController.h"
#include "UI/CustomWD/LAP_ConfirmationWindowWD.h"
#include "UI/MenusWD/LAP_PauseMenu.h"
#include "LAP_GameHUD.generated.h"


class ULAP_MainHUD_WD;
class ULAP_GameOverWindowWD;
class ALAP_BaseLevelManager;
class ULAP_SettingsMenuWD;
class ULAP_LevelsMenuWD;
class ULAP_MainMenuWD;



UCLASS()
class LINESANDPOINTS_API ALAP_GameHUD : public AHUD
{
	GENERATED_BODY()

//public methods
public:

	virtual void BeginPlay() override;

	UFUNCTION()
		void CreateMainMenuWD();
	UFUNCTION()
		void RemoveMainMenuWD();

	UFUNCTION()
		void CreatePauseMenuWD();
	UFUNCTION()
		void RemovePauseMenuWD();

	UFUNCTION()
		void CreateLevelsMenuWD();
	UFUNCTION()
		void RemoveLevelsMenuWD();

	UFUNCTION()
		void CreateSettingsMenuWD();
	UFUNCTION()
		void RemoveSettingsMenuWD();

	UFUNCTION()
		void CreateConfirmWindowWD(FText InConfirmText);
	UFUNCTION()
		void RemoveConfirmWindowWD();

	UFUNCTION()
		void CreateMainHUD_WD(int32 InLevelID = 0);
	UFUNCTION()
		void RemoveMainHUD_WD();

	UFUNCTION()
		void CreateGameOverWindowWD(bool bInPlayerIsWin);
	UFUNCTION()
		void RemoveGameOverWindowWD();

	
	UFUNCTION()
		void RemoveAllWidgets();

//public variables
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<ULAP_MainMenuWD>  MainMenuClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULAP_MainMenuWD* MainMenu = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<ULAP_LevelsMenuWD>  LevelsMenuClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULAP_LevelsMenuWD* LevelsMenu = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<ULAP_SettingsMenuWD>  SettingsMenuClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULAP_SettingsMenuWD* SettingsMenu = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<ULAP_ConfirmationWindowWD>  ConfirmWindowClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULAP_ConfirmationWindowWD* ConfirmWindow = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<ULAP_GameOverWindowWD>  GameOverWindowClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULAP_GameOverWindowWD* GameOverWindow = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<ULAP_MainHUD_WD>  MainHUD_WD_Class;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULAP_MainHUD_WD* MainHUD_WD = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<ULAP_PauseMenu>  PauseMenuClass;
	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
		ULAP_PauseMenu* PauseMenu = nullptr;

	UPROPERTY()
		ALAP_BaseLevelManager* BaseLevelManager = nullptr;

	UPROPERTY()
		ALAP_PlayerController* CustomPlayerController = nullptr;
};
