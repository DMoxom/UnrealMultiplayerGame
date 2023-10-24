// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiplayerAdventureGameMode.h"
#include "MultiplayerAdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiplayerAdventureGameMode::AMultiplayerAdventureGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AMultiplayerAdventureGameMode::HostLANGame()
{
	GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}


void AMultiplayerAdventureGameMode::JoinLANGame()
{
	APlayerController *PC = GetGameInstance()->GetFirstLocalPlayerController();
	if (PC)
	{
		// This is only a local private IP, does not matter if public
		PC->ClientTravel("192.168.0.26", TRAVEL_Absolute);
	}
}
