#include "LobbyWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (startButton)
		startButton->OnClicked.AddDynamic(this, &ULobbyWidget::GameStart);
	if (quitButton)
		quitButton->OnClicked.AddDynamic(this, &ULobbyWidget::GameQuit);
}

void ULobbyWidget::GameStart()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("ShootingMap"));
}

void ULobbyWidget::GameQuit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
