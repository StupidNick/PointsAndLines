#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "LAP_GameSettings.generated.h"



UCLASS(config=GameUserSettings)
class LINESANDPOINTS_API ULAP_GameSettings : public UGameUserSettings
{
	GENERATED_BODY()

public:

	UFUNCTION()
		void SetMenuVibration(bool InValue);

	UFUNCTION()
		void SetGameVibration(bool InValue);

	UPROPERTY(config)
		bool bMenuVibration;

	UPROPERTY(config)
		bool bGameVibration;
};
