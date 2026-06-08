// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AEnemy.h"
#include "ABoss.generated.h"

UCLASS()
class UNREALSHOOTCPP_API ABoss : public AEnemy
{
	GENERATED_BODY()

public:
	ABoss();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void BulletSpawn() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ABullet>> bullets;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> loopCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> loopDelay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float moveTime;	
};
