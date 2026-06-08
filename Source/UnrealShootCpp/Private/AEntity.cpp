#include "AEntity.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

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
	
	bodyMeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, -90.0f));
	bodyMeshComp->SetRelativeScale3D(FVector(1.75f));
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Fabs/3D_LOW_POLY_FarmPack/Meshes/Animals/Birds/SKM_Duck_mixed.SKM_Duck_mixed'"));
	if (tempMesh.Succeeded())
	{
		bodyMeshComp->SetSkeletalMesh(tempMesh.Object);
	}
	
	hpBar = CreateDefaultSubobject<UWidgetComponent>("hpBar");
	hpBar->SetupAttachment(boxComp);
	hpBar->SetWidgetSpace(EWidgetSpace::World);
	
	hpBar->SetRelativeLocation(FVector(0.0f, 0.0f, -70.0f));
	hpBar->SetRelativeRotation(FRotator(180.0f, 0.0f, 0.0f));
	hpBar->SetDrawSize(FVector2D(100.f, 10.f));
	
	ConstructorHelpers::FClassFinder<UUserWidget> tempWidget(TEXT("/Game/Blueprints/Widgets/WBP_HpBar"));
	if (tempWidget.Succeeded())
	{
		hpBar->SetWidgetClass(tempWidget.Class);
	}
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();
	
	curHealth = maxHealth;
	
	if (hpBar)
	{
		hpBarWidget = Cast<UHpBarWidget>(hpBar->GetUserWidgetObject());
		if (hpBarWidget)
		{
			hpBarWidget->UpdateHealth(curHealth, maxHealth);
		}
	}
}

void AEntity::Move(float DeltaTime)
{
	FVector newPos = GetActorLocation() + direction * speed * DeltaTime;
	SetActorLocation(newPos);
}

void AEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isDie)
		return;
	
	Move(DeltaTime);
}

void AEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEntity::GetDamage(TObjectPtr<AActor> Attacker, float Damage)
{
	isHit = true;
	curHealth -= Damage;
	hpBarWidget->UpdateHealth(curHealth, maxHealth);
	if (curHealth <= 0)
		OnDie(this);
	
	if (hitSound)
		UGameplayStatics::PlaySound2D(GetWorld(), hitSound);
	if (hitParticle)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitParticle, GetActorLocation());
}

void AEntity::BulletSpawn()
{
	UWorld* World = GetWorld();
	if (!World)
		return;
	
	FActorSpawnParameters params;
	params.Owner = this;
	World->SpawnActor<ABullet>(bullet, GetActorTransform(), params);
	UGameplayStatics::PlaySound2D(World, bulletSpawnSound);
}


void AEntity::OnDie(TObjectPtr<AActor> Attacker)
{
	curHealth = 0.0f;
	isDie = true;
}

