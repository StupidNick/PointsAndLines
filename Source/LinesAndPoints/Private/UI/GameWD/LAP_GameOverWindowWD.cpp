#include "UI/GameWD/LAP_GameOverWindowWD.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameModes/LAP_GameHUD.h"
#include "GameModes/LAP_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/LAP_PlayerState.h"



void ULAP_GameOverWindowWD::InitializeGameOverWindowWD(ALAP_GameHUD* InGameHUD, bool bInPlayerIsWin)
{
	GameHUD = InGameHUD;

	if (bInPlayerIsWin)
	{
		WinTextBlock->SetText(PlayerWinText);
	}
	else
	{
		WinTextBlock->SetText(PlayerLooseText);
	}

	float LScore;
	ALAP_PlayerState* LPlayerState = Cast<ALAP_PlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (IsValid(LPlayerState))
	{
		LScore = LPlayerState->GetScore();
		LScore = FMath::RoundToZero(LScore);
		ScoreText.Append(FString::SanitizeFloat(LScore, 0));
		ScoreTextBlock->SetText(FText::FromString(ScoreText));
	}
	
	ALAP_GameState* LGameState = Cast<ALAP_GameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (IsValid(LGameState))
	{
		BestScoreText.Append(FString::SanitizeFloat(LGameState->GetCurrentLevelScore().LevelScore, 0));
		BestScoreTextBlock->SetText(FText::FromString(BestScoreText));
	}
	
	MainMenuButton->Button->OnClicked.AddDynamic(this, &ULAP_GameOverWindowWD::OnMainMenuButtonPressed);
	MainMenuButton->SetText(ToMainMenuButtonText);
}


void ULAP_GameOverWindowWD::OnMainMenuButtonPressed()
{
	GameHUD->CreateMainMenuWD();
	GameHUD->RemoveMainHUD_WD();
	GameHUD->RemoveGameOverWindowWD();
}
