// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Engine/World.h"
#include "Gameframework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AShooterAIController::AShooterAIController()
{
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(playerPawn);
}