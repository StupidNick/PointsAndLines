#include "Actors/LAP_Pawn.h"



ALAP_Pawn::ALAP_Pawn()
{
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	SetRootComponent(Camera);
}