#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CheckBox.h"
#include "LAP_CheckBoxWithTextWD.generated.h"


class UTextBlock;
UCLASS()
class LINESANDPOINTS_API ULAP_CheckBoxWithTextWD : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
		void SetCheckBox(bool InValue);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UCheckBox* CheckBox = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (BindWidget))
		UTextBlock* Text = nullptr;
};
