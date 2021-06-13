// Copyright, UE4 tutorial 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	StartingRotation = GetOwner()->GetActorRotation();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	// Check Pressure Plate Overlapping
	if (PressurePlate && PressurePlate->IsOverlappingActor(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Opening door"));
		OpenDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float deltaTime)
{
	float currentYaw = GetOwner()->GetActorRotation().Yaw;
	float newYaw = FMath::FInterpConstantTo(currentYaw, StartingRotation.Yaw + TargetYaw, deltaTime, OpeningSpeed);
	FRotator newRotation{ 0, newYaw, 0 };

	GetOwner()->SetActorRotation(newRotation);
}
