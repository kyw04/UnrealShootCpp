#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "UPlayerAnimInstance.generated.h"

UCLASS()
class UNREALSHOOTCPP_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	void SpawnBullet();
	UFUNCTION(BlueprintCallable)
	void SetPlayerIsAttack(bool value);
	UFUNCTION(BlueprintCallable)
	void SetPlayerIsHit(bool value);
	UFUNCTION(BlueprintCallable)
	void SetPlayerIsDie(bool value);

	UPROPERTY(BlueprintReadWrite, Category = Info)
	bool isAttack;
	UPROPERTY(BlueprintReadWrite, Category = Info)
	bool isHit;
	UPROPERTY(BlueprintReadWrite, Category = Info)
	bool isDie;
	UPROPERTY(BlueprintReadWrite, Category = Info)
	float attackSpeed;
};