#pragma once

#include "CoreMinimal.h"
#include "Actors/LAP_BaseGameObject.h"
#include "GameFramework/PlayerController.h"
#include "GameModes/LAP_PlayerState.h"
#include "LAP_PlayerController.generated.h"


class ULAP_GameSettings;
class ALAP_GameHUD;
UCLASS()
class LINESANDPOINTS_API ALAP_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

public:

	UFUNCTION()
		void OnTapToGameObject(ALAP_BaseGameObject* InGameObject, const ETouchIndex::Type FingerIndex);

	UFUNCTION()
		void OnTapToButton();

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
		ALAP_PlayerState* CustomPlayerState = nullptr;

	UPROPERTY()
		ALAP_GameHUD* GameHUD = nullptr;

	UPROPERTY()
		ULAP_GameSettings* GameSettings = nullptr;

	UPROPERTY(EditDefaultsOnly)
		UForceFeedbackEffect* ForceFeedbackEffect = nullptr;
};
