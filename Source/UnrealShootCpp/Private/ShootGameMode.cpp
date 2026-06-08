#include "ShootGameMode.h"

#include "EnemySpawner.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AShootGameMode::AShootGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> TempBGM(TEXT("/Game/Sounds/background.background"));
	if (TempBGM.Succeeded())
		BGM = TempBGM.Object;
	
	ConstructorHelpers::FClassFinder<ABoss> tempBossClass(TEXT("/Game/Blueprints/Enemies/BP_Boss"));
	if (tempBossClass.Succeeded())
		boss = tempBossClass.Class;
}

void AShootGameMode::BeginPlay()
{
	Super::BeginPlay();
	isBossSpawned = false;
	
	if (BGM)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), BGM);
	}
	
	player = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));
	
	TArray<AActor*> temp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), temp);
	for (auto t : temp)
	{
		if (AEnemySpawner* spawner = Cast<AEnemySpawner>(t))
		{
			spawner->isSpawning = true;
			spawners.Add(spawner);
		}
	}
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->SetInputMode(FInputModeGameOnly());
	}
}

void AShootGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!isBossSpawned && player->score >= 300)
	{
		UE_LOG(LogTemp, Error, TEXT("Bosssssssssssssss"));
		isBossSpawned = true;
		for (auto s : spawners)
			s->isSpawning = false;
		
		GetWorld()->SpawnActor<AEnemy>(boss, FVector(0, 0, 1500), FRotator(0));
	}
}