#include "UI/CustomWD/LAP_ButtonWithID_WD.h"



void ULAP_ButtonWithID_WD::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(Button))
	{
		Button->OnClicked.AddDynamic(this, &ULAP_ButtonWithID_WD::OnButtonClicked);
	}
}


void ULAP_ButtonWithID_WD::OnButtonClicked()
{
	OnButtonClickedCustomEvent.Broadcast(ButtonID);
}
