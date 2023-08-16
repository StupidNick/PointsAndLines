#pragma once

#include "CoreMinimal.h"
#include "LAP_LevelSettingsDA.h"
#include "Engine/DataAsset.h"
#include "LAP_LevelsDA.generated.h"



USTRUCT()
struct FListOfLevels
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		int32 LevelID;

	UPROPERTY(EditAnywhere)
		ULAP_LevelSettingsDA* LevelSettings;

	friend bool operator==(const FListOfLevels& lhs, const FListOfLevels& rhs)
	{
		if (lhs.LevelID == rhs.LevelID && lhs.LevelSettings == rhs.LevelSettings)
		{
			return true;
		}
		return false;
	}
};



UCLASS(BlueprintType)
class LINESANDPOINTS_API ULAP_LevelsDA : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TArray<FListOfLevels> ListOfLevels;
};
