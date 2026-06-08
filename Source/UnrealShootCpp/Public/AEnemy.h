#pragma once

#include "CoreMinimal.h"
#include "AEntity.h"
#include "AEnemy.generated.h"

UCLASS()
class UNREALSHOOTCPP_API AEnemy : public AEntity
{
	GENERATED_BODY()

public:
	AEnemy();

private:
	float curTime;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
