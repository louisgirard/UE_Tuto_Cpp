// Copyright, UE4 tutorial 2021


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "Components/AudioComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	StartingRotation = GetOwner()->GetActorRotation();
	DoorAudio = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!DoorAudio)
	{
		UE_LOG(LogTemp, Warning, TEXT("Audio component missing on %s"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Check Pressure Plate Overlapping
	if (PressurePlate && MassReached())
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
	{
		CloseDoor(DeltaTime);
	}

}

void UOpenDoor::OpenDoor(float deltaTime)
{
	CloseSoundPlayed = false;
	if (!DoorAudio->IsPlaying() && !OpenSoundPlayed)
	{
		DoorAudio->Play();
		OpenSoundPlayed = true;
	}

	float currentYaw = GetOwner()->GetActorRotation().Yaw;
	float newYaw = FMath::FInterpConstantTo(currentYaw, StartingRotation.Yaw + TargetYaw, deltaTime, OpeningSpeed);
	FRotator newRotation{ 0, newYaw, 0 };

	GetOwner()->SetActorRotation(newRotation);
}


void UOpenDoor::CloseDoor(float deltaTime)
{
	OpenSoundPlayed = false;
	if (!DoorAudio->IsPlaying() && !CloseSoundPlayed)
	{
		DoorAudio->Play();
		CloseSoundPlayed = true;
	}

	float currentYaw = GetOwner()->GetActorRotation().Yaw;
	float newYaw = FMath::FInterpConstantTo(currentYaw, StartingRotation.Yaw, deltaTime, ClosingSpeed);
	FRotator newRotation{ 0, newYaw, 0 };

	GetOwner()->SetActorRotation(newRotation);
}

bool UOpenDoor::MassReached()
{
	float currentMass = 0.0f;

	TArray<AActor*> overlappingActors;
	PressurePlate->GetOverlappingActors(overlappingActors);

	// for each actor, sum the mass of their components
	for (auto actor : overlappingActors)
	{
		TArray<UPrimitiveComponent*> components;
		actor->GetComponents(components);

		for (auto component : components)
		{
			currentMass += component->GetMass();
		}
	}

	return currentMass >= MassRequired;
}