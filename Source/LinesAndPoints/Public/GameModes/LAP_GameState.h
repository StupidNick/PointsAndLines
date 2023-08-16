#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "LAP_GameState.generated.h"



class ULAP_LevelSettingsDA;
class ULAP_LevelsDA;



USTRUCT()
struct FLevelScore
{
	GENERATED_BODY()

	UPROPERTY()
	int32 LevelID;

	UPROPERTY()
	float LevelScore;

	friend bool operator==(const FLevelScore& lhs, const FLevelScore& rhs)
	{
		if (lhs.LevelID == rhs.LevelID && lhs.LevelScore == rhs.LevelScore)
		{
			return true;
		}
		return false;
	}
};



UCLASS()
class LINESANDPOINTS_API ALAP_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
	ALAP_GameState();

public:

	UFUNCTION()
		void SetBestLevelScore(float InScore);

	UFUNCTION()
		void SaveGame();

	UFUNCTION()
		void LoadGame();

	UFUNCTION()
		void AddScoreToLevelsList(int32 InLevelID, float InBestScore);

	UFUNCTION()
		ULAP_LevelSettingsDA* FindLevelByID(int32 InLevelID);

	UFUNCTION()
		TArray<FLevelScore> GetLevelsScore();

	UFUNCTION()
		ULAP_LevelsDA* GetListOfLevels();

	UFUNCTION()
		FLevelScore GetCurrentLevelScore();

	UFUNCTION()
		void SetCurrentLevelScore(int32 InLevelID);

	UFUNCTION()
		FLevelScore& FindOrAddLevelScoreByID(int32 InLevelID);
	
private:

	UPROPERTY()
		TArray<FLevelScore> LevelsScore;

	UPROPERTY()
		FLevelScore CurrentLevel;

	UPROPERTY(EditDefaultsOnly)
		ULAP_LevelsDA* ListOfLevelsDA;

	
};
