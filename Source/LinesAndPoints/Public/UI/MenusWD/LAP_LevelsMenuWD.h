#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "LAP_LevelsMenuWD.generated.h"


class ULAP_ButtonWithTextWD;
class UScrollBox;
class ULAP_ButtonWithID_WD;
class ALAP_GameHUD;



UCLASS()
class LINESANDPOINTS_API ULAP_LevelsMenuWD : public UUserWidget
{
	GENERATED_BODY()

//c++ protected methods
protected:

	UPROPERTY()
		int32 ButtonID = -1;

	virtual void NativeConstruct() override;

///////////////////On Buttons clicked////////////////////////////

	UFUNCTION()
		void OnSomeButtonClick(int32 InButtonID);

	UFUNCTION()
		void OnBackButtonClick();


//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "LevelsMenuWD")
		void InitializeLevelsMenu(ALAP_GameHUD* InGameHUD);

	UFUNCTION()
		void CreateLevelsButtons();

	UFUNCTION()
		void OnGameStartConfirmed();


//Blueprint values
public:

	UPROPERTY()
		TArray<ULAP_ButtonWithID_WD*> LevelsButtons;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ULAP_ButtonWithID_WD> ButtonsClass;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UScrollBox* ScrollBox = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UVerticalBox* VerticalBox = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		ULAP_ButtonWithTextWD* BackButton = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "LevelsMenu|Widgets")
		FText BackButtonText;
	UPROPERTY(EditDefaultsOnly, Category = "LevelsMenu|Widgets")
		FText ConfirmText;
	UPROPERTY(EditDefaultsOnly, Category = "LevelsMenu|Widgets")
		FString BestScoreText;
	

	UPROPERTY(BlueprintReadOnly)
		ALAP_GameHUD* GameHUD = nullptr;
};
