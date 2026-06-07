#pragma once

#include "CoreMinimal.h"
#include "ABullet.h"
#include "GameFramework/Pawn.h"
#include "AEntity.generated.h"

UCLASS()
class AEntity : public APawn
{
	GENERATED_BODY()

public:
	AEntity();

protected:
	virtual void BeginPlay() override;
	virtual void Move(float DeltaTime);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void GetDamage(AActor& Attacker, float Damage);
	void BulletSpawn();
	void OnDie(AActor& Attacker);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= ShootComponent)
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere, Category=ShootComponent)
	class UStaticMeshComponent* bodyMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	TSubclassOf<ABullet> bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	float maxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, Category= Stat)
	float curHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	float damage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	float speed = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Info)
	FVector direction;
	UPROPERTY(VisibleAnywhere, Category= Info)
	bool isAttack;
	UPROPERTY(VisibleAnywhere, Category= Info)
	bool isHit;
	UPROPERTY(VisibleAnywhere, Category= Info)
	bool isDie;
};
