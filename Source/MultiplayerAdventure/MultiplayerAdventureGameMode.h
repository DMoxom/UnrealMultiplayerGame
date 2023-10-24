// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerAdventureGameMode.generated.h"

UCLASS(minimalapi)
class AMultiplayerAdventureGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMultiplayerAdventureGameMode();

	UFUNCTION(BlueprintCallable)
	void HostLANGame();

	UFUNCTION(BlueprintCallable)
	void JoinLANGame();
};
