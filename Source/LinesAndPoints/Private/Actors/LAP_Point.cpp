#include "Actors/LAP_Point.h"


ALAP_Point::ALAP_Point()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
}


void ALAP_Point::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetMaterial(0, MeshMaterial);
}


void ALAP_Point::NotifyActorOnInputTouchEnd(const ETouchIndex::Type FingerIndex)
{
	Super::NotifyActorOnInputTouchEnd(FingerIndex);

	OnActivatedEvent.Broadcast(this, FingerIndex);
	OnDestroyedEvent.Broadcast(this, false);
}
