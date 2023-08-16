#include "GameModes/LAP_GameState.h"

#include "Assets/LAP_LevelsDA.h"
#include "GameModes/LAP_SaveGame.h"
#include "Kismet/GameplayStatics.h"


ALAP_GameState::ALAP_GameState()
{
	LoadGame();
}


void ALAP_GameState::SetBestLevelScore(float InScore)
{
	CurrentLevel.LevelScore = FMath::Max(CurrentLevel.LevelScore, InScore);
	AddScoreToLevelsList(CurrentLevel.LevelID, CurrentLevel.LevelScore);
	SaveGame();
	
	UE_LOG(LogTemp, Error, TEXT("Best score: %f"), CurrentLevel.LevelScore);
}


void ALAP_GameState::SaveGame()
{
	ULAP_SaveGame* const LSaveGamInstance = Cast<ULAP_SaveGame>(UGameplayStatics::CreateSaveGameObject(ULAP_SaveGame::StaticClass()));
	if (!IsValid(LSaveGamInstance)) return;

	LSaveGamInstance->LevelsScore = LevelsScore;
	UGameplayStatics::SaveGameToSlot(LSaveGamInstance, TEXT("GameSave"), 0);
}


void ALAP_GameState::LoadGame()
{
	ULAP_SaveGame* LSaveGamInstance = Cast<ULAP_SaveGame>(UGameplayStatics::CreateSaveGameObject(ULAP_SaveGame::StaticClass()));
	if (!IsValid(LSaveGamInstance)) return;

	LSaveGamInstance = Cast<ULAP_SaveGame>(UGameplayStatics::LoadGameFromSlot("GameSave", 0));
	if (!IsValid(LSaveGamInstance)) return;

	LevelsScore = LSaveGamInstance->LevelsScore;
}


void ALAP_GameState::AddScoreToLevelsList(int32 InLevelID, float InBestScore)
{
	FindOrAddLevelScoreByID(InLevelID).LevelScore = InBestScore;
}


ULAP_LevelSettingsDA* ALAP_GameState::FindLevelByID(int32 InLevelID)
{
	if (ListOfLevelsDA->ListOfLevels.IsEmpty()) return nullptr;
	
	for (FListOfLevels& Level : ListOfLevelsDA->ListOfLevels)
	{
		if (Level.LevelID == InLevelID)
		{
			return Level.LevelSettings;
		}
	}
	return nullptr;
}


TArray<FLevelScore> ALAP_GameState::GetLevelsScore()
{
	return LevelsScore;
}


ULAP_LevelsDA* ALAP_GameState::GetListOfLevels()
{
	return ListOfLevelsDA;
}


FLevelScore ALAP_GameState::GetCurrentLevelScore()
{
	return CurrentLevel;
}


void ALAP_GameState::SetCurrentLevelScore(int32 InLevelID)
{
	CurrentLevel = FindOrAddLevelScoreByID(InLevelID);
}


FLevelScore& ALAP_GameState::FindOrAddLevelScoreByID(int32 InLevelID)
{
	for (FLevelScore& Level : LevelsScore)
	{
		if (Level.LevelID == InLevelID)
		{
			return Level;
		}
	}
	
	FLevelScore LNewLevelScore;
	LNewLevelScore.LevelScore = 0.f;
	LNewLevelScore.LevelID = InLevelID;
	LevelsScore.Add(LNewLevelScore);

	const int LIndex = LevelsScore.Find(LNewLevelScore);
	FLevelScore& LTempLevelScore = LevelsScore[LIndex];
	return LTempLevelScore;
}
