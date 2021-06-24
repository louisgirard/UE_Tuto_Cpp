// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Engine/World.h"
#include "Gameframework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector("StartLocation", GetPawn()->GetActorLocation());
	}
}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}