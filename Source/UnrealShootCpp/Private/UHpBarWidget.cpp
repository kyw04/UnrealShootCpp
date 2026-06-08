
#include "UHpBarWidget.h"

void UHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHpBarWidget::UpdateHealth(float CurHealth, float MaxHealth)
{
	if (HealthBar && MaxHealth > 0.f)
	{
		HealthBar->SetPercent(CurHealth / MaxHealth);
	}
}