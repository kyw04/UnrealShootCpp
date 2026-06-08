// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AEntity.h"
#include "ACPlayer.generated.h"

UCLASS()
class UNREALSHOOTCPP_API ACPlayer : public AEntity
{
	GENERATED_BODY()

public:
	ACPlayer();

private:
	bool isOverlapping = false;
	FVector overlapHitNormal = FVector::ZeroVector;
	
protected:
	virtual void BeginPlay() override;
	virtual void Move(float DeltaTime) override;
	void SetDirection(const struct FInputActionValue& value);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void BulletSpawn() override; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Input)
	int score;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Input)
	class UInputAction* ia_move;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Input)
	class UInputAction* ia_shoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Input)
	class UInputMappingContext* imc_shoot;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
