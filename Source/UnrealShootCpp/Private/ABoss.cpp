#include "ABoss.h"

#include "Kismet/GameplayStatics.h"

ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (moveTime > 0)
	{
		moveTime -= DeltaTime;
	}
	else if (!direction.IsNearlyZero())
	{
		direction = FVector::ZeroVector;
	}
}

void ABoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABoss::BulletSpawn()
{
	UWorld* World = GetWorld();
	if (!World)
		return;

	FActorSpawnParameters params;
	params.Owner = this;

	int randomIndex = FMath::RandRange(0, bullets.Num() - 1);
	for (int i = 0; i < loopCount[randomIndex]; i++)
	{
		FTimerHandle timerHandle;
		GetWorld()->GetTimerManager().SetTimer(
			timerHandle,
			[this, randomIndex, params]()
			{
				GetWorld()->SpawnActor<ABullet>(bullets[randomIndex], this->GetActorTransform(), params);
			}, 
			loopDelay[randomIndex] * i + 0.01f,
			false);
		
		UE_LOG(LogTemp, Warning, TEXT("%d"), randomIndex);
		UGameplayStatics::PlaySound2D(World, bulletSpawnSound);
	}
}

