#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "LAP_Pawn.generated.h"



UCLASS()
class LINESANDPOINTS_API ALAP_Pawn : public APawn
{
	GENERATED_BODY()

public:

	ALAP_Pawn();
	
	UPROPERTY(EditDefaultsOnly)
		UCameraComponent* Camera;
};
