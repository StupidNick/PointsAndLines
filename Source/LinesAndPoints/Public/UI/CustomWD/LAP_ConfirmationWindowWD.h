#pragma once

#include "CoreMinimal.h"
#include "LAP_ButtonWithTextWD.h"
#include "Blueprint/UserWidget.h"
#include "LAP_ConfirmationWindowWD.generated.h"



class ALAP_GameHUD;



UCLASS()
class LINESANDPOINTS_API ULAP_ConfirmationWindowWD : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

	UFUNCTION()
		void OnNoButtonClicked();

public:

	UFUNCTION()
		void InitializeConfirmationWindowWD(ALAP_GameHUD* InGameHUD, FText InValue);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		ULAP_ButtonWithTextWD* YesButton = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		ULAP_ButtonWithTextWD* NoButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* ConfirmTextBlock = nullptr;

	UPROPERTY(BlueprintReadOnly)
		ALAP_GameHUD* GameHUD = nullptr;
};
