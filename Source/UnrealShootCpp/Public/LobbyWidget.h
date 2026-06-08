#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "LobbyWidget.generated.h"

UCLASS()
class UNREALSHOOTCPP_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* startButton;
	UPROPERTY(meta = (BindWidget))
	UButton* quitButton;

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void GameStart();
	UFUNCTION(BlueprintCallable)
	void GameQuit();
};
