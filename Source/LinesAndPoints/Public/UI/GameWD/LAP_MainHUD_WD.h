#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UI/CustomWD/LAP_ButtonWithTextWD.h"
#include "LAP_MainHUD_WD.generated.h"


class ALAP_PlayerState;
class ALAP_GameHUD;



UCLASS()
class LINESANDPOINTS_API ULAP_MainHUD_WD : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
		void InitializeMainHUD_WD(ALAP_GameHUD* InGameHUD);

	UFUNCTION()
		void UpdateScore(float InScore);

	UFUNCTION()
		void OnPauseMenuButtonClicked();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainHUD_WD|Widgets")
		UTextBlock* Score;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainHUD_WD|Widgets")
		ULAP_ButtonWithTextWD* PauseMenuButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MainHUD_WD|Widgets")
		FText PauseButtonText;

	UPROPERTY(BlueprintReadOnly)
		ALAP_GameHUD* GameHUD = nullptr;

	UPROPERTY(BlueprintReadOnly)
		ALAP_PlayerState* PlayerState = nullptr;
};
