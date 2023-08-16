#include "PlayerControllers/LAP_PlayerController.h"

#include "GameModes/LAP_GameHUD.h"
#include "GameModes/LAP_GameSettings.h"


void ALAP_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	CustomPlayerState = GetPlayerState<ALAP_PlayerState>();
	GameSettings = Cast<ULAP_GameSettings>(GEngine->GameUserSettings);
}


void ALAP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
}


void ALAP_PlayerController::OnTapToGameObject(ALAP_BaseGameObject* InGameObject, const ETouchIndex::Type FingerIndex)
{
	if (!IsValid(ForceFeedbackEffect) || !IsValid(GameSettings)) return;
	
	if (GameSettings->bGameVibration)
	{
		ClientPlayForceFeedback(ForceFeedbackEffect);
	}
}


void ALAP_PlayerController::OnTapToButton()
{
	if (!IsValid(GameSettings)) return;
	
	if (GameSettings->bMenuVibration)
	{
		ClientPlayForceFeedback(ForceFeedbackEffect);
	}
}


void ALAP_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GameHUD = Cast<ALAP_GameHUD>(GetHUD());
	if (!IsValid(GameHUD)) return;
	
	GameHUD->CreateMainMenuWD();
}
