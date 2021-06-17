// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameModeBase.h"

void ATankGameModeBase::BeginPlay()
{
}

void ATankGameModeBase::ActorDied(AActor* deadActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s died"), *deadActor->GetName());
}

void ATankGameModeBase::HandleGameStart()
{
}

void ATankGameModeBase::HandleGameOver(bool playerWon)
{
}