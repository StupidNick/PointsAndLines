#pragma once

#include "CoreMinimal.h"
#include "LAP_GameStateManager.h"
#include "Assets/LAP_LevelSettingsDA.h"
#include "Components/ActorComponent.h"
#include "GameModes/LAP_GameState.h"
#include "LAP_SpawnManagerComponent.generated.h"


class ALAP_BaseLevelManager;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINESANDPOINTS_API ULAP_SpawnManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	ULAP_SpawnManagerComponent();

	UFUNCTION()
		void OnGameStart(int32 InLevelID);

	UFUNCTION()
		void OnLevelInterrupted();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY()
		int NumOfObjectsToSpawn;

private:

	UFUNCTION()
		void SpawnObject(const FObjectInfo InObjectInfo);

	UFUNCTION()
		void SubscribeToEvents(ALAP_BaseGameObject* GameObject);

	UFUNCTION()
		void InitializeObject(ALAP_BaseGameObject* InGameObject, FObjectInfo InObjectInfo);

	UFUNCTION()
		void OnObjectDestruction(ALAP_BaseGameObject* InGameObject, bool bInDestroyBecauseTimeIsEnd);

	UFUNCTION()
		void DestroyObject(ALAP_BaseGameObject* InGameObject);
	
	UFUNCTION()
		void CheckToGameOver();

	UFUNCTION()
		void GameOver(bool InGameOverWithWin);

	

	UPROPERTY()
		TArray<ALAP_BaseGameObject*> GameObjects;
	

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ULAP_LevelSettingsDA* LevelSettings;

	UPROPERTY()
		ULAP_GameStateManager* GameStateManager = nullptr;

	UPROPERTY()
		ALAP_GameState* GameState = nullptr;

	UPROPERTY()
		ALAP_BaseLevelManager* BaseLevelManger = nullptr;
};
