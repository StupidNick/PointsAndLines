#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/CustomWD/LAP_ConfirmationWindowWD.h"
#include "LAP_SettingsMenuWD.generated.h"


class ULAP_GameSettings;
class ULAP_SliderWithText;
class ULAP_CheckBoxWithTextWD;
class ULAP_ButtonWithTextWD;
class ALAP_GameHUD;
UCLASS()
class LINESANDPOINTS_API ULAP_SettingsMenuWD : public UUserWidget
{
	GENERATED_BODY()

// protected methods
protected:

	virtual void NativeConstruct() override;
	
	void SetupDefaultSettings();

	UFUNCTION()
		void OnVibrationInGameCheckBoxChanged(bool InValue);
	UFUNCTION()
		void OnVibrationInMenuCheckBoxChanged(bool InValue);

	UFUNCTION()
		void OnFPSLimitChanged(float InValue);
	
	UFUNCTION()
		void OnBackButtonClick();


//Blueprint methods
public:

	UFUNCTION()
		void InitializeSettingMenu(ALAP_GameHUD* InGameHUD);


//Blueprint values
public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "SettingsMenu|Widgets")
		ULAP_CheckBoxWithTextWD* MenuVibrationCheckBox = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "SettingsMenu|Widgets")
		ULAP_CheckBoxWithTextWD* GameVibrationCheckBox = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "SettingsMenu|Widgets")
		ULAP_SliderWithText* FPSSlider = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		ULAP_ButtonWithTextWD* BackButton = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "SettingsMenu|Widgets")
		FText GameVibrationText;
	UPROPERTY(EditDefaultsOnly, Category = "SettingsMenu|Widgets")
		FText MenuVibrationText;
	UPROPERTY(EditDefaultsOnly, Category = "SettingsMenu|Widgets")
		FText BackButtonText;
	

	UPROPERTY(BlueprintReadOnly)
		ALAP_GameHUD* GameHUD = nullptr;

	UPROPERTY(BlueprintReadOnly)
		ULAP_GameSettings* GameSettings = nullptr;
};
