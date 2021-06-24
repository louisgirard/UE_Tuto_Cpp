// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "SimpleShooterGameModeBase.h"

void ASimpleShooterGameModeBase::PawnKilled(APawn* PawnKilled)
{
	APlayerController* playerController = Cast<APlayerController>(PawnKilled->GetController());
	if (playerController)
	{
		playerController->GameHasEnded(nullptr, false);
	}
}