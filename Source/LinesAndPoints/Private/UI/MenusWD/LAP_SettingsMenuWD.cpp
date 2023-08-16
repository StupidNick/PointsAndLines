#include "UI/MenusWD/LAP_SettingsMenuWD.h"

#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "GameModes/LAP_GameHUD.h"
#include "GameModes/LAP_GameSettings.h"
#include "Kismet/GameplayStatics.h"
#include "UI/CustomWD/LAP_ButtonWithTextWD.h"
#include "UI/CustomWD/LAP_CheckBoxWithTextWD.h"
#include "UI/CustomWD/LAP_SliderWithText.h"


void ULAP_SettingsMenuWD::NativeConstruct()
{
	Super::NativeConstruct();

	GameSettings = Cast<ULAP_GameSettings>(GEngine->GetGameUserSettings());
	if (IsValid(GameSettings))
	{
		SetupDefaultSettings();
	}

	GameVibrationCheckBox->CheckBox->OnCheckStateChanged.AddDynamic(this, &ULAP_SettingsMenuWD::OnVibrationInGameCheckBoxChanged);
	MenuVibrationCheckBox->CheckBox->OnCheckStateChanged.AddDynamic(this, &ULAP_SettingsMenuWD::OnVibrationInMenuCheckBoxChanged);
	FPSSlider->Slider->OnValueChanged.AddDynamic(this, &ULAP_SettingsMenuWD::OnFPSLimitChanged);
	BackButton->Button->OnClicked.AddDynamic(this, &ULAP_SettingsMenuWD::OnBackButtonClick);

	FPSSlider->Slider->SetMaxValue(60);
	FPSSlider->Slider->SetMinValue(15);
	FPSSlider->Slider->SetStepSize(15);

	BackButton->SetText(BackButtonText);
}


void ULAP_SettingsMenuWD::SetupDefaultSettings()
{
	FPSSlider->SetSliderValue(GameSettings->GetFrameRateLimit());
	MenuVibrationCheckBox->SetCheckBox(GameSettings->bMenuVibration);
	GameVibrationCheckBox->SetCheckBox(GameSettings->bGameVibration);
	
	GameVibrationCheckBox->Text->SetText(GameVibrationText);
	MenuVibrationCheckBox->Text->SetText(MenuVibrationText);
}


void ULAP_SettingsMenuWD::OnBackButtonClick()
{
	GameHUD->CreateMainMenuWD();
	GameHUD->RemoveSettingsMenuWD();
}


void ULAP_SettingsMenuWD::OnVibrationInGameCheckBoxChanged(bool InValue)
{
	GameSettings->SetGameVibration(InValue);
}


void ULAP_SettingsMenuWD::OnVibrationInMenuCheckBoxChanged(bool InValue)
{
	GameSettings->SetMenuVibration(InValue);
}


void ULAP_SettingsMenuWD::OnFPSLimitChanged(float InValue)
{
	GameSettings->SetFrameRateLimit(InValue);
	GameSettings->ApplySettings(false);
}


void ULAP_SettingsMenuWD::InitializeSettingMenu(ALAP_GameHUD* InGameHUD)
{
	GameHUD = InGameHUD;
	BackButton->Button->OnClicked.AddDynamic(GameHUD->CustomPlayerController, &ALAP_PlayerController::OnTapToButton);
}
