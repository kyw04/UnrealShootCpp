#include "EnemySpawner.h"

AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	spawnTime = 0;
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	spawnTime += FMath::RandRange(0.0f, spawnMaxPlusTime);
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (!isSpawning)
		return;

	spawnTime += DeltaTime;
	if (spawnTime >= spawnDelay)
	{
		float add = FMath::RandRange(0.0f, spawnMaxPlusTime);
		spawnTime -= spawnDelay - add;
		
		UWorld* World = GetWorld();
		if (!World)
			return;
	
		auto target = enemies[FMath::RandRange(0, enemies.Num() - 1)];
		World->SpawnActor<AEnemy>(target, GetActorTransform());
	}
}

void AEnemySpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

