#include "AEnemy.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	curTime = 0.0f;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
    Tags.Add(FName("Enemy"));
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bullet)
	{
		curTime += DeltaTime;
		if (curTime >= bulletDelay)
		{
			curTime -= bulletDelay;
			BulletSpawn();
		}
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

