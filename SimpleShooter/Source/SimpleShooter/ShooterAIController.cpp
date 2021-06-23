// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Engine/World.h"
#include "Gameframework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AShooterAIController::AShooterAIController()
{
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);
		Blackboard = GetBlackboardComponent();
		Blackboard->SetValueAsVector("PlayerLocation", PlayerPawn->GetActorLocation());
		Blackboard->SetValueAsVector("StartLocation", GetPawn()->GetActorLocation());
	}
}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LineOfSightTo(PlayerPawn))
	{
		Blackboard->SetValueAsVector("PlayerLocation", PlayerPawn->GetActorLocation());
		Blackboard->SetValueAsVector("LastKnowPlayerLocation", PlayerPawn->GetActorLocation());
	}
	else
	{
		Blackboard->ClearValue("PlayerLocation");
	}

}