#include "UI/MenusWD/LAP_PauseMenu.h"

#include "Actors/LAP_BaseLevelManager.h"
#include "Components/Button.h"
#include "Components/LAP_GameStateManager.h"
#include "Components/TextBlock.h"
#include "GameModes/LAP_GameHUD.h"


void ULAP_PauseMenu::InitializePauseMenu(ALAP_GameHUD* InGameHUD)
{
	GameHUD = InGameHUD;

	GameHUD->GetOwningPlayerController()->SetPause(true);
	TextBlock->SetText(PauseText);
	BackToMenuButton->Button->OnClicked.AddDynamic(this, &ULAP_PauseMenu::OnBackToMenuButtonClicked);
	ContinueButton->Button->OnClicked.AddDynamic(this, &ULAP_PauseMenu::OnContinueButtonClicked);
	BackToMenuButton->SetText(BackToMenuText);
	ContinueButton->SetText(ContinueText);
}


void ULAP_PauseMenu::OnBackToMenuButtonClicked()
{
	GameHUD->GetOwningPlayerController()->SetPause(false);
	GameHUD->BaseLevelManager->GameStateManager->LevelInterruptedEvent.Broadcast();
	GameHUD->RemoveMainHUD_WD();
	GameHUD->CreateMainMenuWD();
	GameHUD->RemovePauseMenuWD();
}


void ULAP_PauseMenu::OnContinueButtonClicked()
{
	GameHUD->GetOwningPlayerController()->SetPause(false);
	GameHUD->RemovePauseMenuWD();
}
