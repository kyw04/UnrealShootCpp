// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AEntity.h"
#include "ACPlayer.generated.h"

UCLASS()
class UNREALSHOOTCPP_API ACPlayer : public AEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input");
	class UInputAction* ia_move;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input");
	class UInputAction* ia_shoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input");
	class UInputMappingContext* imc_shoot;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
