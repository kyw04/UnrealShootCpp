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
	boxComp->SetBoxExtent(FVector(40, 20, 40));
	
	bodyMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMeshComp"));
	bodyMeshComp->SetupAttachment(boxComp);
	bodyMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Fabs/3D_LOW_POLY_FarmPack/Meshes/Animals/Birds/SKM_Duck_mixed.SKM_Duck_mixed'"));
	if (tempMesh.Succeeded())
	{
		bodyMeshComp->SetSkeletalMesh(tempMesh.Object);
		bodyMeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, -90.0f));
		bodyMeshComp->SetRelativeScale3D(FVector(1.75f));
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

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
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
	
	World->SpawnActor<ABullet>(bullet, GetActorTransform())->Owner = this;
}


void AEntity::OnDie(AActor& Attacker)
{
	curHealth = 0.0f;
	isDie = true;
}

