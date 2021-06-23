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

	// AI look at player
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	SetFocus(PlayerPawn);
}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// AI follow player
	MoveToActor(PlayerPawn, 200);

}