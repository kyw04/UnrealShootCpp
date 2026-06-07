#pragma once

#include "CoreMinimal.h"

#include "ABullet.generated.h"

UCLASS()
class UNREALSHOOTCPP_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	ABullet();

private:
	TArray<FVector> realtimePositions;
	float currentTime;
	
protected:
	virtual void BeginPlay() override;
	TArray<FVector> SetPosition(TArray<FVector> pos);
	TArray<FVector> RotatePosition(TArray<FVector> pos, float degrees);
	
public:
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
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Stat)
	float damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Stat)
	float speed;
};
