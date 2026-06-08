#include "ShootGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AShootGameMode::AShootGameMode()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> TempBGM(TEXT("/Game/Sounds/background.background"));

	if (TempBGM.Succeeded())
	{
		BGM = TempBGM.Object;
	}
}

void AShootGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (BGM)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BGM);
	}
}