// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "SimpleShooterGameModeBase.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	FTimerHandle restartHandle;
	FTimerDelegate restartDelegate = FTimerDelegate::CreateUObject(this, &APlayerController::RestartLevel);
	GetWorld()->GetTimerManager().SetTimer(restartHandle, restartDelegate, RestartDelay, false);

	GameOverUI(bIsWinner);
}