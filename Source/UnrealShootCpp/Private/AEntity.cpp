#include "AEntity.h"

#include "Components/BoxComponent.h"
#include "InputActionValue.h"
#include "GameFramework/Actor.h"

AEntity::AEntity()
{
	PrimaryActorTick.bCanEverTick = true;
	
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = boxComp;
	boxComp->SetCollisionProfileName(TEXT("OverlapAll"));
	
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp->SetupAttachment(boxComp);
	bodyMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	if (tempMesh.Succeeded())
	{
		bodyMeshComp->SetStaticMesh(tempMesh.Object);
	}
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();
	
	curHealth = maxHealth;
}

void AEntity::Move(float DeltaTime)
{
	FVector newPos = GetActorLocation() + direction * speed * DeltaTime;
	SetActorLocation(newPos);
}

void AEntity::SetDirection(const FInputActionValue& value)
{
	auto v = value.Get<FVector>();
	direction.Y = v.X;
	direction.Z = v.Y;
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	direction = FVector::Zero();
}

void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEntity::GetDamage(AActor& Attacker, float Damage)
{
	curHealth -= Damage;
	if (curHealth <= 0)
	{
		OnDie(*this);
	}
}

void AEntity::BulletSpawn()
{
	UWorld* World = GetWorld();
	if (!World)
		return;
	
	World->SpawnActor<ABullet>(bullet, GetActorTransform());
}


void AEntity::OnDie(AActor& Attacker)
{
	curHealth = 0.0f;
	isDie = true;
}

