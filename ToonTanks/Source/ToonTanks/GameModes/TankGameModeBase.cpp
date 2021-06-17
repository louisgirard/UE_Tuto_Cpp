// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

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
	TArray<AActor*> turrets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), turrets);
	NumberOfTurrets = turrets.Num();

	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	GameStart();
}

void ATankGameModeBase::HandleGameOver(bool playerWon)
{
	GameOver(playerWon);
}