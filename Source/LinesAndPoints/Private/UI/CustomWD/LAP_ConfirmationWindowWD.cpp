#include "UI/CustomWD/LAP_ConfirmationWindowWD.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameModes/LAP_GameHUD.h"


void ULAP_ConfirmationWindowWD::NativeConstruct()
{
	Super::NativeConstruct();
	
	NoButton->Button->OnClicked.AddDynamic(this, &ULAP_ConfirmationWindowWD::OnNoButtonClicked);
}


void ULAP_ConfirmationWindowWD::OnNoButtonClicked()
{
	GameHUD->CustomPlayerController->OnTapToButton();
	GameHUD->RemoveConfirmWindowWD();
}


void ULAP_ConfirmationWindowWD::InitializeConfirmationWindowWD(ALAP_GameHUD* InGameHUD, FText InValue)
{
	GameHUD = InGameHUD;
	ConfirmTextBlock->SetText(InValue);

	YesButton->SetText(FText::FromString("Yes"));
	NoButton->SetText(FText::FromString("No"));
}
