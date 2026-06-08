#pragma once

#include "CoreMinimal.h"
#include "ACPlayer.h"
#include "AEnemy.h"
#include "EnemySpawner.generated.h"

UCLASS()
class UNREALSHOOTCPP_API AEnemySpawner : public APawn
{
	GENERATED_BODY()

public:
	AEnemySpawner();

private:
	float spawnTime;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float spawnDelay;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float spawnMaxPlusTime;
		
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<AEnemy>> enemies;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ACPlayer* player;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool isSpawning;
};
