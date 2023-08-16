#include "UI/CustomWD/LAP_SliderWithText.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"


void ULAP_SliderWithText::NativeConstruct()
{
	Super::NativeConstruct();

	Slider->OnValueChanged.AddDynamic(this, &ULAP_SliderWithText::OnSliderChanged);
}

void ULAP_SliderWithText::OnSliderChanged(float InSliderValue)
{
	Text->SetText(FText::AsNumber(InSliderValue));
}


void ULAP_SliderWithText::SetSliderValue(float InSliderValue)
{
	Slider->SetValue(InSliderValue);
	OnSliderChanged(InSliderValue);
}
