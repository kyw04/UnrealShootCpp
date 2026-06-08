#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyWidget.h"
#include "Sound/SoundBase.h"
#include "LobbyGameMode.generated.h"

UCLASS()
class UNREALSHOOTCPP_API ALobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALobbyGameMode();
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	class ULobbyWidget* lobbyWidget;
	UPROPERTY()
	class TSubclassOf<UUserWidget> lobbyWidgetClass;

	USoundBase* BGM;
};