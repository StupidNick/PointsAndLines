#include "Actors/LAP_BaseGameObject.h"

#include "Components/LAP_SpawnManagerComponent.h"


void ALAP_BaseGameObject::Initialize(FObjectInfo InObjectInfo)
{
	LifeTime = InObjectInfo.LifeTime;
	PointsForClick = InObjectInfo.MaxPointForInteract;
	PointsForPass = InObjectInfo.CollectPointsForPass;

	FTimerHandle LTimerHandle;
	FTimerDelegate LTimerDelegate;
	
	LTimerDelegate.BindUObject(this, &ALAP_BaseGameObject::OnTimerEnded);
	GetWorldTimerManager().SetTimer(LTimerHandle, LTimerDelegate, LifeTime, false);
}


void ALAP_BaseGameObject::OnTimerEnded()
{
	SetHidden(true);
	OnDestroyedEvent.Broadcast(this, true);
}


void ALAP_BaseGameObject::DisableCollision()
{
}
