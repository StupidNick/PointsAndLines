#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LAP_ButtonWithTextWD.generated.h"



class UTextBlock;
class UButton;



UCLASS()
class LINESANDPOINTS_API ULAP_ButtonWithTextWD : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
		void SetText(FText InText);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Button = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Text = nullptr;
};
