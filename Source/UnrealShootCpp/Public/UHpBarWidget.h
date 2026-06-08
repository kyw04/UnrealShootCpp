#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "UHpBarWidget.generated.h"

UCLASS()
class UNREALSHOOTCPP_API UHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateHealth(float CurHealth, float MaxHealth);
};
