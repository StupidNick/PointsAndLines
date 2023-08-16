#include "GameModes/LAP_PlayerState.h"



void ALAP_PlayerState::ChangePlayerScore(const float InPoints)
{
	SetScore(FMath::Max(0, GetScore() + InPoints));
	OnPlayerScoreChanged.Broadcast(GetScore());
}


void ALAP_PlayerState::ClearPlayerScore()
{
	SetScore(0);
	OnPlayerScoreChanged.Broadcast(GetScore());
}


int ALAP_PlayerState::GetHealth() const
{
	return Health;
}


void ALAP_PlayerState::SetHealth(int InHealth)
{
	Health = InHealth;
}


void ALAP_PlayerState::RemoveHealth()
{
	Health--;
}
