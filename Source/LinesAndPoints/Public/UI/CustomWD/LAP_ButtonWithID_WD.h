#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Blueprint/UserWidget.h"
#include "LAP_ButtonWithID_WD.generated.h"


class UTextBlock;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonClickedCustomEvent, int32, ButtonID);


UCLASS()
class LINESANDPOINTS_API ULAP_ButtonWithID_WD : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeConstruct() override;

public:

	UFUNCTION()
		void OnButtonClicked();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Button = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Text = nullptr;

	UPROPERTY()
		int32 ButtonID;

	UPROPERTY()
		FOnButtonClickedCustomEvent OnButtonClickedCustomEvent;
};
