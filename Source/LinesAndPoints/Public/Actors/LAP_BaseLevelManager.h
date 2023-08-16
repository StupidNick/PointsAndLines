#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LAP_BaseLevelManager.generated.h"


class ULAP_GameStateManager;
class ULAP_PlayerScoreManager;
class ULAP_SpawnManagerComponent;


UCLASS()
class LINESANDPOINTS_API ALAP_BaseLevelManager : public AActor
{
	GENERATED_BODY()
	
public:	

	ALAP_BaseLevelManager();

protected:

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		ULAP_SpawnManagerComponent* SpawnManagerComponent = nullptr;

	UPROPERTY(EditAnywhere)
		ULAP_PlayerScoreManager* PlayerScoreManager = nullptr;

	UPROPERTY(EditAnywhere)
		ULAP_GameStateManager* GameStateManager = nullptr;

};
