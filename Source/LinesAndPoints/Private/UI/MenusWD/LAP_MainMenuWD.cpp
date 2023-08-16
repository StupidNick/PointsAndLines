#include "UI/MenusWD/LAP_MainMenuWD.h"

#include "Components/Button.h"
#include "GameModes/LAP_GameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


void ULAP_MainMenuWD::NativeConstruct()
{
	Super::NativeConstruct();

	if (LevelsButton)
	{
		LevelsButton->OnClicked.AddDynamic(this, &ULAP_MainMenuWD::OnLevelsButtonClick);
	}
	if (SettingsButton)
	{
		SettingsButton->OnClicked.AddDynamic(this, &ULAP_MainMenuWD::OnSettingsButtonClick);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &ULAP_MainMenuWD::OnExitButtonClick);
	}
}


void ULAP_MainMenuWD::InitializeMainMenu(ALAP_GameHUD* InGameHUD)
{
	GameHUD = InGameHUD;
}


void ULAP_MainMenuWD::OnLevelsButtonClick()
{
	GameHUD->CustomPlayerController->OnTapToButton();
	GameHUD->CreateLevelsMenuWD();
	GameHUD->RemoveMainMenuWD();
}


void ULAP_MainMenuWD::OnSettingsButtonClick()
{
	GameHUD->CustomPlayerController->OnTapToButton();
	GameHUD->CreateSettingsMenuWD();
	GameHUD->RemoveMainMenuWD();
}


void ULAP_MainMenuWD::OnExitButtonClick()
{
	GameHUD->CustomPlayerController->OnTapToButton();
	GameHUD->CreateConfirmWindowWD(ConfirmText);
	GameHUD->ConfirmWindow->YesButton->Button->OnClicked.AddDynamic(this, &ULAP_MainMenuWD::OnExitConfirmed);
}


void ULAP_MainMenuWD::OnExitConfirmed()
{
	GameHUD->RemoveConfirmWindowWD();
	GameHUD->RemoveMainMenuWD();
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, true);
}
