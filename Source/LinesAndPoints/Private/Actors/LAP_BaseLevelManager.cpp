#include "Actors/LAP_BaseLevelManager.h"

#include "Components/LAP_PlayerScoreManager.h"
#include "Components/LAP_SpawnManagerComponent.h"
#include "Components/LAP_GameStateManager.h"
#include "Kismet/GameplayStatics.h"


ALAP_BaseLevelManager::ALAP_BaseLevelManager()
{
	PrimaryActorTick.bCanEverTick = true;

	SpawnManagerComponent = CreateDefaultSubobject<ULAP_SpawnManagerComponent>("SpawnManagerComponent");
	PlayerScoreManager = CreateDefaultSubobject<ULAP_PlayerScoreManager>("PlayerScoreManager");
	GameStateManager = CreateDefaultSubobject<ULAP_GameStateManager>("GameStateManager");
}


void ALAP_BaseLevelManager::BeginPlay()
{
	Super::BeginPlay();
}