#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LAP_PauseMenu.generated.h"


class UTextBlock;
class ULAP_ButtonWithTextWD;
class ALAP_GameHUD;



UCLASS()
class LINESANDPOINTS_API ULAP_PauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
		void InitializePauseMenu(ALAP_GameHUD* InGameHUD);

	UFUNCTION()
		void OnBackToMenuButtonClicked();
	UFUNCTION()
		void OnContinueButtonClicked();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "PauseMenu|Widgets")
		ULAP_ButtonWithTextWD* BackToMenuButton = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "PauseMenu|Widgets")
		ULAP_ButtonWithTextWD* ContinueButton = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "PauseMenu|Widgets")
		UTextBlock* TextBlock = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "PauseMenu|Widgets")
		FText PauseText;
	UPROPERTY(EditDefaultsOnly, Category = "PauseMenu|Widgets")
		FText BackToMenuText;
	UPROPERTY(EditDefaultsOnly, Category = "PauseMenu|Widgets")
		FText ContinueText;
	

	UPROPERTY(BlueprintReadOnly)
		ALAP_GameHUD* GameHUD = nullptr;
};
