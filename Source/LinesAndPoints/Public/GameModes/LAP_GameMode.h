#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LAP_GameMode.generated.h"



UCLASS()
class LINESANDPOINTS_API ALAP_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
};
