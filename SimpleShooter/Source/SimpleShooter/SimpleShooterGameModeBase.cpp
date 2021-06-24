// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SimpleShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "ShooterAIController.h"

void ASimpleShooterGameModeBase::BeginPlay()
{
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<AActor*> enemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterAIController::StaticClass(), enemies);
	InitialNumberOfEnemies = enemies.Num();
	NumberOfEnemies = InitialNumberOfEnemies;
}

void ASimpleShooterGameModeBase::PawnKilled(APawn* PawnKilled)
{
	if (PlayerController == Cast<APlayerController>(PawnKilled->GetController()))
	{
		PlayerController->GameHasEnded(nullptr, false);
		GameOver(false);
	}
	else if (AAIController* aiController = Cast<AAIController>(PawnKilled->GetController()))
	{
		NumberOfEnemies = FMath::Max(0.f, NumberOfEnemies - 1);
		if (NumberOfEnemies == 0)
		{
			PlayerController->GameHasEnded(aiController, true);
			GameOver(true);
		}
	}
}