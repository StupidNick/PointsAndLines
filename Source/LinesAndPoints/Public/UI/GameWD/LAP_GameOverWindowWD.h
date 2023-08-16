#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/CustomWD/LAP_ButtonWithTextWD.h"
#include "LAP_GameOverWindowWD.generated.h"


class ALAP_GameHUD;
class UTextBlock;



UCLASS()
class LINESANDPOINTS_API ULAP_GameOverWindowWD : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
		void InitializeGameOverWindowWD(ALAP_GameHUD* InGameHUD, bool bInPlayerIsWin);

	UFUNCTION()
		void OnMainMenuButtonPressed();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "GameOverWindow|Widgets")
		ULAP_ButtonWithTextWD* MainMenuButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "GameOverWindow|Widgets")
		UTextBlock* WinTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "GameOverWindow|Widgets")
		UTextBlock* ScoreTextBlock = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "GameOverWindow|Widgets")
		UTextBlock* BestScoreTextBlock = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "GameOverWindow|Widgets")
		FText PlayerWinText;
	UPROPERTY(EditDefaultsOnly, Category = "GameOverWindow|Widgets")
		FText PlayerLooseText;
	UPROPERTY(EditDefaultsOnly, Category = "GameOverWindow|Widgets")
		FText ToMainMenuButtonText;
	UPROPERTY(EditDefaultsOnly, Category = "GameOverWindow|Widgets")
		FString ScoreText;
	UPROPERTY(EditDefaultsOnly, Category = "GameOverWindow|Widgets")
		FString BestScoreText;


	UPROPERTY(BlueprintReadOnly)
		ALAP_GameHUD* GameHUD = nullptr;
};
