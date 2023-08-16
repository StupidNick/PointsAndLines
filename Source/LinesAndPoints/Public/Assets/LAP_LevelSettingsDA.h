#pragma once

#include "CoreMinimal.h"
#include "Actors/LAP_Line.h"
#include "Actors/LAP_Point.h"
#include "Engine/DataAsset.h"
#include "LAP_LevelSettingsDA.generated.h"


class ALAP_BaseGameObject;


UENUM(BlueprintType)
enum EObjectType
{
	Point,
	Line,
};


USTRUCT(BlueprintType)
struct FObjectInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.1", ClampMax = "100.0"), Category = "Time")
		float TimeBeforeSpawn = 1;

	UPROPERTY(EditDefaultsOnly, meta = (ClampMin = "0.1", ClampMax = "100.0"), Category = "Time")
		float LifeTime = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Score")
		int MaxPointForInteract;

	UPROPERTY(EditDefaultsOnly, Category = "Score")
		int CollectPointsForPass;

	UPROPERTY(EditAnywhere, Category = "Types")
		TEnumAsByte<EObjectType> ObjectType;

	UPROPERTY(EditDefaultsOnly, meta=(EditCondition="ObjectType==EObjectType::Point", EditConditionHides), Category = "Types")
		TSubclassOf<ALAP_Point> SpawnPointClass;

	UPROPERTY(EditDefaultsOnly, meta=(EditCondition="ObjectType==EObjectType::Line", EditConditionHides), Category = "Types")
		TSubclassOf<ALAP_Line> SpawnLineClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition="ObjectType==EObjectType::Point", EditConditionHides), Category = "Transforms")
		FTransform SpawnTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(EditCondition="ObjectType==EObjectType::Line", EditConditionHides), Category = "Transforms")
		TArray<FTransform> SpawnLineTransforms;
};


UCLASS()
class LINESANDPOINTS_API ULAP_LevelSettingsDA : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TArray<FObjectInfo> ObjectsInfoArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		int DefaultPlayerHealth = 5;
};
