#include "AEnemy.h"
#include "Components/BoxComponent.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	curTime = 0.0f;
	
	if (bodyMeshComp)
	{
		bodyMeshComp->SetRelativeRotation(FRotator(180.0f, -90.0f, -90.0f));
	}
	
	ConstructorHelpers::FObjectFinder<UNiagaraSystem> tempHitParticle(TEXT("/Game/Fabs/Generic_Item_Destruction_FX/Visual_Effects/NiagaraSystem/NS_Paper.NS_Paper"));
	if (tempHitParticle.Succeeded())
		hitParticle = tempHitParticle.Object;
	
	// ConstructorHelpers::FObjectFinder<USoundBase> tempBulletSound(TEXT("/Game/Sounds/laying_egg.laying_egg"));
	// if (tempBulletSound.Succeeded())
	// 	bulletSpawnSound = tempBulletSound.Object;
	ConstructorHelpers::FObjectFinder<USoundBase> tempHitSound(TEXT("/Game/Sounds/Chicken_Hit.Chicken_Hit"));
	if (tempHitSound.Succeeded())
		hitSound = tempHitSound.Object;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (boxComp)
	{
		boxComp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnBeginOverlap);
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isDie)
		return;
	
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

void AEnemy::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || OtherActor == this || OtherActor->Owner == this)
		return;
	if (Cast<AEnemy>(OtherActor))
		return;
	
	if (Cast<ABullet>(OtherActor))
	{
		GetDamage(OtherActor->Owner, Cast<ABullet>(OtherActor)->damage);
		OtherActor->Destroy();
	}
}

