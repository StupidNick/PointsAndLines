#include "UI/GameWD/LAP_MainHUD_WD.h"

#include "Components/Button.h"
#include "GameModes/LAP_GameHUD.h"
#include "GameModes/LAP_PlayerState.h"
#include "Kismet/GameplayStatics.h"


void ULAP_MainHUD_WD::InitializeMainHUD_WD(ALAP_GameHUD* InGameHUD)
{
	GameHUD = InGameHUD; 
	PlayerState = Cast<ALAP_PlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
	if (IsValid(PlayerState))
	{
		PlayerState->OnPlayerScoreChanged.AddDynamic(this, &ULAP_MainHUD_WD::UpdateScore);
	}
	PauseMenuButton->Button->OnClicked.AddDynamic(this, &ULAP_MainHUD_WD::OnPauseMenuButtonClicked);
	PauseMenuButton->SetText(PauseButtonText);
}


void ULAP_MainHUD_WD::UpdateScore(float InScore)
{
	InScore = FMath::RoundToZero(InScore);
	FString LText = "Your score: ";
	LText.Append(FString::SanitizeFloat(InScore, 0));
	Score->SetText(FText::FromString(LText));
}


void ULAP_MainHUD_WD::OnPauseMenuButtonClicked()
{
	GameHUD->CreatePauseMenuWD();
}
