#include "LobbyGameMode.h"

#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

ALobbyGameMode::ALobbyGameMode()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> TempBGM(TEXT("/Game/Sounds/background.background"));
	if (TempBGM.Succeeded())
		BGM = TempBGM.Object;
	
	ConstructorHelpers::FClassFinder<UUserWidget> tempWidget(TEXT("/Game/Blueprints/Widgets/WBP_LobbyWidget"));
	if (tempWidget.Succeeded())
		lobbyWidgetClass = tempWidget.Class;
}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (BGM)
		UGameplayStatics::PlaySound2D(GetWorld(), BGM);
	
	if (lobbyWidgetClass)
	{
		lobbyWidget = Cast<ULobbyWidget>(CreateWidget<UUserWidget>(GetWorld(), lobbyWidgetClass));
		if (lobbyWidget)
			lobbyWidget->AddToViewport();
	}
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeUIOnly());
	}
}
