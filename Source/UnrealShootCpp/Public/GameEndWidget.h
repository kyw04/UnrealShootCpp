#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameEndWidget.generated.h"

UCLASS()
class UNREALSHOOTCPP_API UGameEndWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* restartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* quitButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* gameEndText;
	
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void OnGameEndWidget(FText endText);
	UFUNCTION(BlueprintCallable)
	void OffGameEndWidget();
	
	UFUNCTION(BlueprintCallable)
	void GameRestart();
	UFUNCTION(BlueprintCallable)
	void GameQuit();
};
