#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LAP_MainMenuWD.generated.h"



class ALAP_GameHUD;
class UButton;



UCLASS()
class LINESANDPOINTS_API ULAP_MainMenuWD : public UUserWidget
{
	GENERATED_BODY()

	
//c++ protected methods
protected:

	virtual void NativeConstruct() override;

///////////////////On Buttons clicked////////////////////////////

	UFUNCTION()
		void OnLevelsButtonClick();
	UFUNCTION()
		void OnSettingsButtonClick();
	UFUNCTION()
		void OnExitButtonClick();
	UFUNCTION()
		void OnExitConfirmed();


//Blueprint methods
public:

	UFUNCTION(BlueprintCallable, Category = "MainMenuWD")
		void InitializeMainMenu(ALAP_GameHUD* InGameHUD);


//Blueprint values
public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenuWD|Widgets")
		UButton* LevelsButton = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenuWD|Widgets")
		UButton* SettingsButton = nullptr;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget), Category = "MainMenuWD|Widgets")
		UButton* ExitButton = nullptr;


	UPROPERTY(EditDefaultsOnly, Category = "LevelsMenu|Widgets")
		FText ConfirmText;
	

	UPROPERTY(BlueprintReadOnly)
		ALAP_GameHUD* GameHUD = nullptr;
};
