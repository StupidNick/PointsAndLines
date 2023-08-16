#pragma once

#include "CoreMinimal.h"
#include "Actors/LAP_BaseGameObject.h"
#include "Components/ActorComponent.h"
#include "LAP_GameStateManager.generated.h"


class ULAP_SpawnManagerComponent;
class ALAP_PlayerState;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameOverEvent, bool, bGameOverWithWin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelInterruptedEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameStartEvent, int, GameLevelID);



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LINESANDPOINTS_API ULAP_GameStateManager : public UActorComponent
{
	GENERATED_BODY()

public:
	
	ULAP_GameStateManager();

	UFUNCTION()
		void OnGameObjectDestruction(ALAP_BaseGameObject* InGameObject, bool bInDestroyBecauseTimeIsEnd);

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnGameStart(int InGameLevelID);

public:

	UPROPERTY()
		FGameOverEvent GameOverEvent;

	UPROPERTY()
		FGameStartEvent GameStartEvent;
	UPROPERTY()
		FLevelInterruptedEvent LevelInterruptedEvent;

	UPROPERTY()
		ALAP_PlayerState* CustomPlayerState;

	UPROPERTY()
		ULAP_SpawnManagerComponent* SpawnManagerComponent;
};
