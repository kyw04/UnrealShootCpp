// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this pawn's properties
	AEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetDirection(const struct FInputActionValue& value);
	virtual void Move(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void GetDamage(AActor& Attacker, float Damage);
	void BulletSpawn();
	void OnDie(AActor& Attacker);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= ShootComponent)
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere, Category=ShootComponent)
	class UStaticMeshComponent* bodyMeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	ABullet* Bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	float maxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, Category= Stat)
	float curHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	float bulletDamage = 10.0f;
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
