#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Sound/SoundBase.h"
#include "ShootGameMode.generated.h"

UCLASS()
class UNREALSHOOTCPP_API AShootGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShootGameMode();
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* BGM;
};