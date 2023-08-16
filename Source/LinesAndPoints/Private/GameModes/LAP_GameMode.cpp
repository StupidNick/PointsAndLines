#include "GameModes/LAP_GameMode.h"

#include "GameModes/LAP_GameSettings.h"

void ALAP_GameMode::BeginPlay()
{
	Super::BeginPlay();

	ULAP_GameSettings* LGameSettings = Cast<ULAP_GameSettings>(GEngine->GetGameUserSettings());
	if (IsValid(LGameSettings))
	{
		LGameSettings->LoadSettings();
	}
}
