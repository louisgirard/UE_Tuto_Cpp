// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	APlayerController* PlayerController;

	float NumberOfEnemies;
	float InitialNumberOfEnemies;

public:
	void PawnKilled(APawn* PawnKilled);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
