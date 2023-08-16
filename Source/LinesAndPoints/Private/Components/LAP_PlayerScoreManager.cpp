#include "Components/LAP_PlayerScoreManager.h"

#include "Actors/LAP_BaseGameObject.h"
#include "Actors/LAP_Line.h"
#include "Actors/LAP_Point.h"
#include "Components/LAP_GameStateManager.h"
#include "GameFramework/GameModeBase.h"
#include "GameModes/LAP_GameState.h"
#include "GameModes/LAP_PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


ULAP_PlayerScoreManager::ULAP_PlayerScoreManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void ULAP_PlayerScoreManager::BeginPlay()
{
	Super::BeginPlay();

	CustomPlayerState = Cast<ALAP_PlayerState>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->PlayerState);
	ULAP_GameStateManager* LGameStateManager = Cast<ALAP_BaseLevelManager>(GetOwner())->GameStateManager;
	if (IsValid(LGameStateManager))
	{
		LGameStateManager->GameOverEvent.AddDynamic(this, &ULAP_PlayerScoreManager::OnGameOver);
		LGameStateManager->GameStartEvent.AddDynamic(this, &ULAP_PlayerScoreManager::ClearScore);
	}
}


void ULAP_PlayerScoreManager::ClearScore(int32 InLevelID)
{
	if (!IsValid(CustomPlayerState)) return;
	CustomPlayerState->ClearPlayerScore();
}


void ULAP_PlayerScoreManager::ChangeScore(ALAP_BaseGameObject* InGameObject, ETouchIndex::Type InFinger)
{
	if (!IsValid(CustomPlayerState)) return;
	
	ALAP_Line* LLine = Cast<ALAP_Line>(InGameObject);
	if (IsValid(LLine))
	{
		CustomPlayerState->ChangePlayerScore(CountScoreForLine(LLine));
		return;
	}

	ALAP_Point* LPoint = Cast<ALAP_Point>(InGameObject);
	if (IsValid(LPoint))
	{
		CustomPlayerState->ChangePlayerScore(CountScoreForPoint(LPoint, InFinger));
	}
}


void ULAP_PlayerScoreManager::OnObjectDestroyed(ALAP_BaseGameObject* InGameObject, bool bInDestroyBecauseTimeIsEnd)
{
	if (!IsValid(InGameObject) || !IsValid(CustomPlayerState)) return;

	if (bInDestroyBecauseTimeIsEnd)
	{
		CustomPlayerState->ChangePlayerScore(-UKismetMathLibrary::Abs(InGameObject->PointsForPass));
	}
}


float ULAP_PlayerScoreManager::CountScoreForPoint(ALAP_Point* InGameObject, ETouchIndex::Type InFinger) const
{
	const FVector LWorldLocation = GetWorldLocationOfTouch(InFinger);
	const float Distance = FVector::Distance(FVector(InGameObject->GetActorLocation().X, InGameObject->GetActorLocation().Y, 0.f), FVector(LWorldLocation.X, LWorldLocation.Y, 0.f));

	if (Distance <= InGameObject->MaxDistanceToExcellentClick)
	{
		return InGameObject->PointsForClick;
	}
	if (Distance >= InGameObject->MaxDistanceForClick)
	{
		return 0;
	}
	return InGameObject->PointsForClick * (1 - Distance / InGameObject->MaxDistanceForClick);
}


float ULAP_PlayerScoreManager::CountScoreForLine(ALAP_Line* InGameObject) const
{
	if (InGameObject->MinDistanceToPoint <= InGameObject->MaxDistanceToExcellentClick)
	{
		return InGameObject->PointsForClick;
	}
	return InGameObject->PointsForClick * (1 - InGameObject->MinDistanceToPoint / InGameObject->MaxDistanceForClick);
}


FVector ULAP_PlayerScoreManager::GetWorldLocationOfTouch(ETouchIndex::Type InFinger) const
{
	float XLocation, YLocation;
	FVector WorldLocation, WorldDirection;
	bool CurrentlyPressed;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetInputTouchState(InFinger, XLocation, YLocation, CurrentlyPressed);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(XLocation, YLocation, WorldLocation, WorldDirection);
	WorldLocation *= 100.f;
	return WorldLocation;
}


void ULAP_PlayerScoreManager::OnGameOver(bool InPlayerIsWin)
{
	if (InPlayerIsWin)
	{
		ALAP_GameState* LGameState = Cast<ALAP_GameState>(GetWorld()->GetGameState<ALAP_GameState>());
		if (IsValid(LGameState))
		{
			LGameState->SetBestLevelScore(CustomPlayerState->GetScore());
		}
	}
}