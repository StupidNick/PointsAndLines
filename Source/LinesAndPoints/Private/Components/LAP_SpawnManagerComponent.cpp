#include "Components/LAP_SpawnManagerComponent.h"

#include "Actors/LAP_BaseGameObject.h"
#include "Actors/LAP_BaseLevelManager.h"
#include "Components/LAP_GameStateManager.h"
#include "Components/LAP_PlayerScoreManager.h"
#include "GameModes/LAP_GameHUD.h"
#include "GameModes/LAP_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerControllers/LAP_PlayerController.h"



ULAP_SpawnManagerComponent::ULAP_SpawnManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void ULAP_SpawnManagerComponent::OnGameStart(int32 InLevelID)
{
	if (!IsValid(GameState)) return;
	LevelSettings = GameState->FindLevelByID(InLevelID);
	
	if (!IsValid(LevelSettings)) return;
	if (LevelSettings->ObjectsInfoArray.IsEmpty()) return;

	NumOfObjectsToSpawn = LevelSettings->ObjectsInfoArray.Num();
	for (FObjectInfo LObjectInfo : LevelSettings->ObjectsInfoArray)
	{
		FTimerHandle LTimerHandle;
		FTimerDelegate LTimerDelegate;
		
		LTimerDelegate.BindUObject(this, &ULAP_SpawnManagerComponent::SpawnObject, LObjectInfo);
		GetWorld()->GetTimerManager().SetTimer(LTimerHandle, LTimerDelegate, LObjectInfo.TimeBeforeSpawn, false);
	}
}


void ULAP_SpawnManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	BaseLevelManger = Cast<ALAP_BaseLevelManager>(GetOwner());
	if (!IsValid(BaseLevelManger)) return;

	ALAP_PlayerController* LPlayerController = Cast<ALAP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ALAP_GameHUD* LGameHUD = Cast<ALAP_GameHUD>(LPlayerController->GetHUD());
	if (IsValid(LGameHUD))
	{
		LGameHUD->BaseLevelManager = BaseLevelManger;
	}

	GameState = Cast<ALAP_GameState>(GetWorld()->GetGameState<ALAP_GameState>());
	GameStateManager = Cast<ALAP_BaseLevelManager>(GetOwner())->GameStateManager;
	if (IsValid(GameStateManager))
	{
		GameStateManager->GameOverEvent.AddDynamic(this, &ULAP_SpawnManagerComponent::GameOver);
		GameStateManager->GameStartEvent.AddDynamic(this, &ULAP_SpawnManagerComponent::OnGameStart);
		if (IsValid(LGameHUD))
		{
			GameStateManager->GameOverEvent.AddDynamic(LGameHUD, &ALAP_GameHUD::CreateGameOverWindowWD);
			GameStateManager->GameStartEvent.AddDynamic(LGameHUD, &ALAP_GameHUD::CreateMainHUD_WD);
		}
	}
}


void ULAP_SpawnManagerComponent::SpawnObject(const FObjectInfo InObjectInfo)
{
	NumOfObjectsToSpawn--;
	
	ALAP_BaseGameObject* LObject = nullptr;
	if (InObjectInfo.ObjectType == Line)
	{
		LObject = GetWorld()->SpawnActor<ALAP_BaseGameObject>(InObjectInfo.SpawnLineClass, InObjectInfo.SpawnLineTransforms[0], FActorSpawnParameters());
	}
	if (InObjectInfo.ObjectType == Point)
	{
		LObject = GetWorld()->SpawnActor<ALAP_BaseGameObject>(InObjectInfo.SpawnPointClass, InObjectInfo.SpawnTransform, FActorSpawnParameters());
	}
	if (!IsValid(LObject))
	{
		return;
	}
	
	GameObjects.Add(LObject);
	SubscribeToEvents(LObject);
	InitializeObject(LObject, InObjectInfo);
}


void ULAP_SpawnManagerComponent::SubscribeToEvents(ALAP_BaseGameObject* GameObject)
{
	GameObject->OnDestroyedEvent.AddDynamic(this, &ULAP_SpawnManagerComponent::OnObjectDestruction);
	
	const ULAP_PlayerScoreManager* LPlayerScoreManager = Cast<ALAP_BaseLevelManager>(GetOwner())->PlayerScoreManager;
	if (IsValid(LPlayerScoreManager))
	{
		GameObject->OnActivatedEvent.AddDynamic(LPlayerScoreManager, &ULAP_PlayerScoreManager::ChangeScore);
		GameObject->OnDestroyedEvent.AddDynamic(LPlayerScoreManager, &ULAP_PlayerScoreManager::OnObjectDestroyed);
	}
	const ALAP_PlayerController* LPlayerController = Cast<ALAP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (IsValid(LPlayerController))
	{
		GameObject->OnActivatedEvent.AddDynamic(LPlayerController, &ALAP_PlayerController::OnTapToGameObject);
	}
	if (IsValid(GameStateManager))
	{
		GameObject->OnDestroyedEvent.AddDynamic(GameStateManager, &ULAP_GameStateManager::OnGameObjectDestruction);
	}
}


void ULAP_SpawnManagerComponent::InitializeObject(ALAP_BaseGameObject* InGameObject, FObjectInfo InObjectInfo)
{
	InGameObject->Initialize(InObjectInfo);
}


void ULAP_SpawnManagerComponent::OnObjectDestruction(ALAP_BaseGameObject* InGameObject, bool bInDestroyBecauseTimeIsEnd)
{
	if (!IsValid(InGameObject))
	{
		return;
	}
	
	GetWorld()->GetTimerManager().ClearTimer(InGameObject->LifeTimerHandle);
	
	FTimerHandle LTimerHandle;
	FTimerDelegate LTimerDelegate;
		
	LTimerDelegate.BindUObject(this, &ULAP_SpawnManagerComponent::DestroyObject, InGameObject);
	GetWorld()->GetTimerManager().SetTimer(LTimerHandle, LTimerDelegate, .1f, false);
}


void ULAP_SpawnManagerComponent::DestroyObject(ALAP_BaseGameObject* InGameObject)
{
	GameObjects.Remove(InGameObject);
	InGameObject->Destroy();
	
	CheckToGameOver();
}


void ULAP_SpawnManagerComponent::CheckToGameOver()
{
	if (!IsValid(GameStateManager)) return;
	
	if (GameObjects.IsEmpty() && NumOfObjectsToSpawn <= 0)
	{
		GameStateManager->GameOverEvent.Broadcast(true);
	}
}


void ULAP_SpawnManagerComponent::GameOver(bool InGameOverWithWin)
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
	if (!GameObjects.IsEmpty())
	{
		for (ALAP_BaseGameObject* LGameObject : GameObjects)
		{
			GetWorld()->GetTimerManager().ClearAllTimersForObject(LGameObject);
			LGameObject->Destroy();
		}
		GameObjects.Empty();
	}
}


void ULAP_SpawnManagerComponent::OnLevelInterrupted()
{
	GameOver(false);
}


