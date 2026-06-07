#include "ACPlayer.h"

#include "Components/BoxComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	if (boxComp) 
	{
		boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACPlayer::OnBeginOverlap);
		boxComp->OnComponentEndOverlap.AddDynamic(this, &ACPlayer::OnEndOverlap);
	}
}

void ACPlayer::SetDirection(const struct FInputActionValue& value)
{
	Super::SetDirection(value);
	
	if (direction.Y * overlapHitNormal.Y > 0.0f)
		overlapHitNormal.Y = 0.0f;
	if (direction.Z * overlapHitNormal.Z > 0.0f)
		overlapHitNormal.Z = 0.0f;
}

void ACPlayer::Move(float DeltaTime)
{
	FVector moveDir = direction;

	if (isOverlapping)
		moveDir = (FVector::OneVector - overlapHitNormal.GetAbs()) * moveDir;

	FVector newPos = GetActorLocation() + moveDir * speed * DeltaTime;
	SetActorLocation(newPos, true);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	auto pc = Cast<APlayerController>(Controller);
	if (pc)
	{
		auto subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subsystem)
		{
			subsystem->AddMappingContext(imc_shoot, 0);
		}
	}
	
	auto playerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (playerInput)
	{
		playerInput->BindAction(ia_move, ETriggerEvent::Triggered, this, &ACPlayer::SetDirection);
	}
}

void ACPlayer::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
	FString::Printf(TEXT("bFromSweep=%d  ImpactNormal=%s  Normal=%s"),
		bFromSweep,
		*SweepResult.ImpactNormal.ToString(),
		*SweepResult.Normal.ToString()));
	
	if (!OtherActor || OtherActor == this)
		return;

	FVector n = SweepResult.ImpactNormal;
	n.X = 0.0f;
	if (n.IsNearlyZero())
		return;

	if (isOverlapping)
		overlapHitNormal += n;
	else
		overlapHitNormal = n;
	
	overlapHitNormal.Y = FMath::Clamp(overlapHitNormal.Y, -1.0f, 1.0f);
	overlapHitNormal.Z = FMath::Clamp(overlapHitNormal.Z, -1.0f, 1.0f);
	
	isOverlapping = true;
}

void ACPlayer::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor || OtherActor == this)
		return;
	
	FVector dir = (OtherActor->GetActorLocation() - GetActorLocation()).GetAbs();
	if (dir.Y < dir.Z)
		overlapHitNormal.Y = 0.0f;
	else
		overlapHitNormal.Z = 0.0f;

	isOverlapping = !overlapHitNormal.IsNearlyZero();
}