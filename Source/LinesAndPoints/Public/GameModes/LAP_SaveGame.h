#pragma once

#include "CoreMinimal.h"
#include "LAP_GameState.h"
#include "GameFramework/SaveGame.h"
#include "LAP_SaveGame.generated.h"


// struct FLevelScore;



UCLASS()
class LINESANDPOINTS_API ULAP_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
		TArray<FLevelScore> LevelsScore;
};
