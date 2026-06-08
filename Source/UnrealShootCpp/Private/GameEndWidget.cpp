#include "GameEndWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UGameEndWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (restartButton)
		restartButton->OnClicked.AddDynamic(this, &UGameEndWidget::GameRestart);
	if (quitButton)
		quitButton->OnClicked.AddDynamic(this, &UGameEndWidget::GameQuit);

	this->SetVisibility(ESlateVisibility::Hidden);
}

void UGameEndWidget::OnGameEndWidget(FText endText)
{
	gameEndText->SetText(endText);
	this->SetVisibility(ESlateVisibility::Visible);
}

void UGameEndWidget::OffGameEndWidget()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}

void UGameEndWidget::GameRestart()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("ShootingMap"));
}

void UGameEndWidget::GameQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
