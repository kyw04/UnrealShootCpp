#pragma once

#include "AEntity.h"
#include "UScoreBoard.h"
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

	UPROPERTY()
	UScoreBoard* scoreWidget;
	UPROPERTY()
	TSubclassOf<UUserWidget> scoreBoardClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Input)
	int32 score;
	
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
