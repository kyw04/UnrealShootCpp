// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ABullet.generated.h"

UCLASS()
class UNREALSHOOTCPP_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

private:
	TArray<FVector> realtimePositions;
	float currentTime;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<FVector> SetPosition(TArray<FVector> pos);
	TArray<FVector> RotatePosition(TArray<FVector> pos, float degrees);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	FVector GetBezierCurvePosition();
	int32 Combination(int32 n, int32 r);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= ShootComponent)
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere, Category= ShootComponent)
	class UStaticMeshComponent* bodyMeshComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Bezier)
	TArray<FVector> positions;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Bezier)
	float angle;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Bezier)
	bool loop;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Bezier)
	float damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Bezier)
	float pointDistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Bezier)
	float speed;
};
