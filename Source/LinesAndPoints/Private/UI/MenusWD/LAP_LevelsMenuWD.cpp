#include "UI/MenusWD/LAP_LevelsMenuWD.h"

#include "Actors/LAP_BaseLevelManager.h"
#include "Assets/LAP_LevelsDA.h"
#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/LAP_GameStateManager.h"
#include "Components/TextBlock.h"
#include "GameModes/LAP_GameHUD.h"
#include "GameModes/LAP_GameState.h"
#include "UI/CustomWD/LAP_ButtonWithTextWD.h"
#include "UI/CustomWD/LAP_ButtonWithID_WD.h"


void ULAP_LevelsMenuWD::NativeConstruct()
{
	Super::NativeConstruct();

	BackButton->Button->OnClicked.AddDynamic(this, &ULAP_LevelsMenuWD::OnBackButtonClick);
	
	BackButton->SetText(BackButtonText);
}


void ULAP_LevelsMenuWD::OnBackButtonClick()
{
	GameHUD->CustomPlayerController->OnTapToButton();
	GameHUD->CreateMainMenuWD();
	GameHUD->RemoveLevelsMenuWD();
}


void ULAP_LevelsMenuWD::OnSomeButtonClick(int32 InButtonID)
{
	ButtonID = InButtonID;

	GameHUD->CustomPlayerController->OnTapToButton();
	GameHUD->CreateConfirmWindowWD(ConfirmText);
	GameHUD->ConfirmWindow->YesButton->Button->OnClicked.AddDynamic(this, &ULAP_LevelsMenuWD::OnGameStartConfirmed);
	GameHUD->ConfirmWindow->YesButton->Button->OnClicked.AddDynamic(GameHUD->CustomPlayerController, &ALAP_PlayerController::OnTapToButton);
}


void ULAP_LevelsMenuWD::InitializeLevelsMenu(ALAP_GameHUD* InGameHUD)
{
	GameHUD = InGameHUD;
	CreateLevelsButtons();
}


void ULAP_LevelsMenuWD::CreateLevelsButtons()
{
	ALAP_GameState* LGameState = Cast<ALAP_GameState>(GetWorld()->GetGameState<ALAP_GameState>());
	if (!IsValid(LGameState)) return;

	TArray<FListOfLevels> LLevelsList = LGameState->GetListOfLevels()->ListOfLevels;
	for (FListOfLevels List : LLevelsList)
	{
		UHorizontalBox* LHorizontalBox = WidgetTree->ConstructWidget<UHorizontalBox>(UHorizontalBox::StaticClass(), TEXT("HorizontalBox"));
		if (!IsValid(LHorizontalBox)) continue;
		
		UTextBlock* LTextBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass(), TEXT("TextBlock"));
		if (!IsValid(LTextBlock)) continue;
		
		FLevelScore LScore = LGameState->FindOrAddLevelScoreByID(List.LevelID);
		FString LBestScoreSting = BestScoreText;
		LScore.LevelScore = FMath::RoundToZero(LScore.LevelScore);
		LBestScoreSting.Append(FString::SanitizeFloat(LScore.LevelScore, 0));
		LTextBlock->SetText(FText::FromString(LBestScoreSting));
		FSlateColor LNewColor = FSlateColor(FLinearColor(.0f, .0f, .0f, 1.0f));
		LTextBlock->SetColorAndOpacity(LNewColor);
		
		ULAP_ButtonWithID_WD* LButton = CreateWidget<ULAP_ButtonWithID_WD>(GetWorld(), ButtonsClass);
		if (!IsValid(LButton)) continue;

		LButton->ButtonID = List.LevelID;

		FString LButtonText = "Level ";
		LButtonText.Append(FString::FromInt(LButton->ButtonID));
		LButton->Text->SetText(FText::FromString(LButtonText));

		LButton->Padding.Top = 10;
		LButton->Padding.Bottom = 30;
		LButton->Padding.Right = 30;
		
		LButton->OnButtonClickedCustomEvent.AddDynamic(this, &ULAP_LevelsMenuWD::OnSomeButtonClick);
		LButton->Button->OnClicked.AddDynamic(GameHUD->CustomPlayerController, &ALAP_PlayerController::OnTapToButton);
		
		LHorizontalBox->AddChild(LButton);
		LHorizontalBox->AddChild(LTextBlock);
		VerticalBox->AddChild(LHorizontalBox);

		LevelsButtons.Add(LButton);
	}
}


void ULAP_LevelsMenuWD::OnGameStartConfirmed()
{
	GameHUD->CustomPlayerController->OnTapToButton();
	
	ALAP_GameState* LGameState = Cast<ALAP_GameState>(GetWorld()->GetGameState<ALAP_GameState>());
	if (!IsValid(LGameState)) return;

	if (IsValid(LGameState->FindLevelByID(ButtonID)))
	{
		GameHUD->BaseLevelManager->GameStateManager->GameStartEvent.Broadcast(ButtonID);
		GameHUD->RemoveConfirmWindowWD();
		GameHUD->RemoveLevelsMenuWD();
		return;
	}
	GameHUD->RemoveConfirmWindowWD();
}
