#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "LAP_PlayerState.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerScoreChanged, float, PlayerScore);



UCLASS()
class LINESANDPOINTS_API ALAP_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	UFUNCTION()
		void ChangePlayerScore(const float InPoints);

	UFUNCTION()
		void ClearPlayerScore();

	UFUNCTION()
		int GetHealth() const;

	UFUNCTION()
		void SetHealth(int InHealth);

	UFUNCTION()
		void RemoveHealth();

	UPROPERTY()
		FOnPlayerScoreChanged OnPlayerScoreChanged;
	
private:

	UPROPERTY()
		int Health;
};
