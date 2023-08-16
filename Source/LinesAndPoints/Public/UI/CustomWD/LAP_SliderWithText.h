#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LAP_SliderWithText.generated.h"



class USlider;
class UTextBlock;



UCLASS()
class LINESANDPOINTS_API ULAP_SliderWithText : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

public:

	UFUNCTION()
		void OnSliderChanged(float InSliderValue);

	UFUNCTION()
		void SetSliderValue(float InSliderValue);
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		USlider* Slider = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Text = nullptr;
};
