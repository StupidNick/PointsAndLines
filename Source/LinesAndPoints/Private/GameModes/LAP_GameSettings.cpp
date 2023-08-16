#include "GameModes/LAP_GameSettings.h"



void ULAP_GameSettings::SetMenuVibration(bool InValue)
{
	bMenuVibration = InValue;
	ApplySettings(true);
}


void ULAP_GameSettings::SetGameVibration(bool InValue)
{
	bGameVibration = InValue;
	ApplySettings(true);
}
