// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"




void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// ItemTitle can be nullptr if we haven't created it in the
	// Blueprint subclass
	if (Player1LifeLabel)
	{
		Player1LifeLabel->SetText(FText::FromString(TEXT("Player 1: ")));
	}
	if (Player2LifeLabel)
	{
		Player2LifeLabel->SetText(FText::FromString(TEXT("Player 2: ")));
	}
	if (HighScoreLabel)
	{
		HighScoreLabel->SetText(FText::FromString(TEXT("Time To Beat: ")));

	}
	if (CurrentScoreLabel)
	{
		CurrentScoreLabel->SetText(FText::FromString(TEXT("Current Time: ")));
	}
}

void UHUDWidget::UpdateLifeTotal(int32 NewHealth, int32 PlayerId) {

	const FString UpdatedText = FString::Printf(TEXT("Player %i: %i"), PlayerId + 1, NewHealth);
	UE_LOG(LogTemp, Warning, TEXT("Updating health"));

	if (PlayerId == 0)
	{
		Player1LifeLabel->SetText(FText::FromString(UpdatedText));
	}
	
	if (PlayerId == 1)
	{

		Player2LifeLabel->SetText(FText::FromString(UpdatedText));
	}
	

}
void UHUDWidget::UpdateCurrentScore(FTimespan TimeSpan) {
	FString UpdatedText = FString::Printf(TEXT("Current Time: "));
	UpdatedText.Append(TimeSpan.ToString());
	CurrentScoreLabel->SetText(FText::FromString(UpdatedText));
}

void UHUDWidget::UpdateTimeToBeat(FTimespan TimeSpan) {
	FString UpdatedText = FString::Printf(TEXT("Time To Beat: "));
	UpdatedText.Append(TimeSpan.ToString());
	HighScoreLabel->SetText(FText::FromString(UpdatedText));
}

