#pragma once

#include "CoreMinimal.h"
#include "ABullet.h"
#include "GameFramework/Pawn.h"
#include "UHpBarWidget.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "AEntity.generated.h"

UCLASS()
class UNREALSHOOTCPP_API AEntity : public APawn
{
	GENERATED_BODY()

public:
	AEntity();

private:
	UPROPERTY()
	UHpBarWidget* hpBarWidget;
	
protected:
	virtual void BeginPlay() override;
	virtual void Move(float DeltaTime);

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BulletSpawn();
	void GetDamage(TObjectPtr<AActor> Attacker, float Damage);
	void OnDie(TObjectPtr<AActor> Attacker);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category= ShootComponent)
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere, Category=ShootComponent)
	class USkeletalMeshComponent* bodyMeshComp;
	UPROPERTY(VisibleAnywhere, Category=ShootComponent)
	class UWidgetComponent* hpBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Particle)
	class UNiagaraSystem* hitParticle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Sound)
	USoundBase* bulletSpawnSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Sound)
	USoundBase* hitSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	TSubclassOf<ABullet> bullet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	float maxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Stat)
	float curHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	float damage = 10.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Stat)
	float speed = 500.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category= Stat)
	float bulletDelay = 1.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Info)
	FVector direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Info)
	bool isAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Info)
	bool isHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Info)
	bool isDie;
};
