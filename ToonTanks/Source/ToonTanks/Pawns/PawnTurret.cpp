// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTurret.h"
#include "PawnTank.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/PlayerController.h"

// Sets default values
APawnTurret::APawnTurret()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckTargetInRange, FireRate, true);
	PawnTank = Cast<APawnTank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateTurret(PawnTank->GetActorLocation());
}

void APawnTurret::CheckTargetInRange()
{
	if (!PawnTank) return;

	float distanceWithTarget = FVector::DistXY(GetActorLocation(), PawnTank->GetActorLocation());
	
	if (distanceWithTarget <= FireRange)
	{
		Fire();
	}
}

void APawnTurret::Destruction()
{
	Super::Destruction();
	Destroy();
}