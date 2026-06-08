#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UScoreBoard.generated.h"

UCLASS()
class UNREALSHOOTCPP_API UScoreBoard : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* scoreText;

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateScore(int32 score);
};
