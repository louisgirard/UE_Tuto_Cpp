// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"
#include "GameFramework/Pawn.h"

void APlayerControllerBase::SetPlayerEnable(bool enable)
{
	if (enable)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = enable;
}