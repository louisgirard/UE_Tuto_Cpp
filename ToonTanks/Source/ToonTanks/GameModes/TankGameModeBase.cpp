// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* deadActor)
{
	if (deadActor == PlayerTank)
	{
		PlayerTank->Destruction();
		HandleGameOver(false);

		PlayerController->SetPlayerEnable(false);
	}
	else if(APawnTurret* deadTurret = Cast<APawnTurret>(deadActor))
	{
		deadTurret->Destruction();

		NumberOfTurrets--;
		if (NumberOfTurrets <= 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	// Get Actors
	TArray<AActor*> turrets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), turrets);
	NumberOfTurrets = turrets.Num();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	PlayerController = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	// BP Start
	GameStart();

	// Enable Inputs
	PlayerController->SetPlayerEnable(false);
	
	FTimerHandle playerEnableHandle;
	FTimerDelegate playerEnableDelegate = FTimerDelegate::CreateUObject(PlayerController, &APlayerControllerBase::SetPlayerEnable, true);
	GetWorld()->GetTimerManager().SetTimer(playerEnableHandle, playerEnableDelegate, CountdownDelay + 1, false);
}

void ATankGameModeBase::HandleGameOver(bool playerWon)
{
	GameOver(playerWon);
}