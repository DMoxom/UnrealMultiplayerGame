// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Alternative to SetReplicates(true)
	//bReplicates = true;
}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();

	replicatedVar = 100.0f;

	SetReplicates(true);
	SetReplicateMovement(true);

	if (HasAuthority())
	{
		GetWorld()->GetTimerManager().SetTimer(testTimer, this, &AMyBox::DecreasedReplicatedVar, 2.0f, false);
	}
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if(HasAuthority())
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("Server"));
	// }
	// else
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("Client"));
	// }

	// if (GetLocalRole() == ROLE_Authority)
	// {

	// }
}

void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyBox, replicatedVar);
}

void AMyBox::OnRep_ReplicatedVar()
{
	if (!HasAuthority())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, 
			FString::Printf(TEXT("Client %d: OnRep_ReplicatedVar"), GPlayInEditorID));
		return;
	}

	FVector newLocation = GetActorLocation() + FVector(0.0f, 0.0f, 200.0f);
	SetActorLocation(newLocation);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Server: OnRep_ReplicatedVar"));
}

void AMyBox::DecreasedReplicatedVar()
{
	if (!HasAuthority())
	{
		return;
	}

	replicatedVar -= 1.0f;
	OnRep_ReplicatedVar();

	if (replicatedVar > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(testTimer, this, &AMyBox::DecreasedReplicatedVar, 2.0f, false);
	}
}
