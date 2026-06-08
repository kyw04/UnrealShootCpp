#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sound/SoundBase.h"
#include "ABoss.h"
#include "ACPlayer.h"
#include "EnemySpawner.h"
#include "ShootGameMode.generated.h"

UCLASS()
class UNREALSHOOTCPP_API AShootGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootGameMode();
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AEnemySpawner*> spawners;
	UPROPERTY()
	TSubclassOf<ABoss> boss;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACPlayer *player;

private:
	bool isBossSpawned;
	
protected:
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* BGM;
};