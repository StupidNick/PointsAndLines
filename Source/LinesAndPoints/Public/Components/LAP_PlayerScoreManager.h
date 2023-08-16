#pragma once

#include "CoreMinimal.h"
#include "Actors/LAP_BaseLevelManager.h"
#include "Components/ActorComponent.h"
#include "LAP_PlayerScoreManager.generated.h"


class ALAP_PlayerState;
class ALAP_BaseGameObject;
class ALAP_Point;
class ALAP_Line;



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINESANDPOINTS_API ULAP_PlayerScoreManager : public UActorComponent
{
	GENERATED_BODY()

public:	

	ULAP_PlayerScoreManager();

protected:

	virtual void BeginPlay() override;

public:

	UFUNCTION()
		void ClearScore(int32 InLevelID = 0);

	UFUNCTION()
		void ChangeScore(ALAP_BaseGameObject* InGameObject, ETouchIndex::Type InFinger);

	UFUNCTION()
		void OnObjectDestroyed(ALAP_BaseGameObject* InGameObject, bool bInDestroyBecauseTimeIsEnd);

	UFUNCTION()
		float CountScoreForPoint(ALAP_Point* InGameObject, ETouchIndex::Type InFinger) const;

	UFUNCTION()
		float CountScoreForLine(ALAP_Line* InGameObject) const;

	UFUNCTION()
		FVector GetWorldLocationOfTouch(ETouchIndex::Type InFinger) const;

	UFUNCTION()
		void OnGameOver(bool InPlayerIsWin);

	UPROPERTY()
		ALAP_BaseLevelManager* LevelManager = nullptr;

	UPROPERTY()
		ALAP_PlayerState* CustomPlayerState = nullptr;
};
