// Fill out your copyright notice in the Description page of Project Settings.


#include "AEntity.h"

#include "Components/BoxComponent.h"
#include "InputActionValue.h"

// Sets default values
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

// Called when the game starts or when spawned
void AEntity::BeginPlay()
{
	Super::BeginPlay();
	
	curHealth = maxHealth;
}

void AEntity::Move(float DeltaTime)
{
	FVector newPos = GetActorLocation() + direction * speed * DeltaTime;
	SetActorLocation(newPos, true);
}

void AEntity::SetDirection(const FInputActionValue& value)
{
	auto v = value.Get<FVector>();
	direction.Y = v.X;
	direction.Z = v.Y;
}

// Called every frame
void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
	direction = FVector::Zero();
}

// Called to bind functionality to input
void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEntity::TakeDamage(float Damage)
{
}


void AEntity::OnDie(AActor& Attacker)
{
	curHealth = 0.0f;
	isDie = true;
}

