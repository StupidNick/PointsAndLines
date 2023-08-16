#include "Components/LAP_GameStateManager.h"

#include "Actors/LAP_BaseLevelManager.h"
#include "Components/LAP_SpawnManagerComponent.h"
#include "GameModes/LAP_PlayerState.h"
#include "Kismet/GameplayStatics.h"


ULAP_GameStateManager::ULAP_GameStateManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void ULAP_GameStateManager::OnGameObjectDestruction(ALAP_BaseGameObject* InGameObject, bool bInDestroyBecauseTimeIsEnd)
{
	if (!IsValid(CustomPlayerState) || !bInDestroyBecauseTimeIsEnd) return;

	CustomPlayerState->RemoveHealth();
	if (CustomPlayerState->GetHealth() <= 0)
	{
		GameOverEvent.Broadcast(false);
	}
}


void ULAP_GameStateManager::BeginPlay()
{
	Super::BeginPlay();

	SpawnManagerComponent = Cast<ALAP_BaseLevelManager>(GetOwner())->SpawnManagerComponent;
	CustomPlayerState = Cast<ALAP_PlayerState>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerState);
	
	if (!IsValid(CustomPlayerState) || !IsValid(SpawnManagerComponent)) return;

	GameStartEvent.AddDynamic(SpawnManagerComponent->GameState, &ALAP_GameState::SetCurrentLevelScore);
	GameStartEvent.AddDynamic(this, &ULAP_GameStateManager::OnGameStart);
	LevelInterruptedEvent.AddDynamic(SpawnManagerComponent, &ULAP_SpawnManagerComponent::OnLevelInterrupted);
}


void ULAP_GameStateManager::OnGameStart(int InGameLevelID)
{
	CustomPlayerState->SetHealth(SpawnManagerComponent->LevelSettings->DefaultPlayerHealth);
}
