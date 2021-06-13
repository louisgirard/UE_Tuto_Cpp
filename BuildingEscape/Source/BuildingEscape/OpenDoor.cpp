// Copyright, UE4 tutorial 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"

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

	// Calculate new rotation
	float currentYaw = GetOwner()->GetActorRotation().Yaw;
	float newYaw = FMath::FInterpConstantTo(currentYaw, StartingRotation.Yaw + TargetYaw, DeltaTime, OpeningSpeed);
	FRotator newRotation{ 0, newYaw, 0 };

	GetOwner()->SetActorRotation(newRotation);

	UE_LOG(LogTemp, Warning, TEXT("Yaw: %f"), GetOwner()->GetActorRotation().Yaw);
}

