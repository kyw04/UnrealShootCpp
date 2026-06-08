#include "UScoreBoard.h"

void UScoreBoard::NativeConstruct()
{
	Super::NativeConstruct();
}

void UScoreBoard::UpdateScore(int32 score)
{
	if (scoreText)
	{
		scoreText->SetText(FText::FromString(FString::FromInt(score)));
	}
}