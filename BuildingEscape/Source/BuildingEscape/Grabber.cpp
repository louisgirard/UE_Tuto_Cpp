// Copyright, UE4 tutorial 2021


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector playerLocation;
	FRotator playerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotation);

	FVector lineTraceEnding = playerRotation.Vector() * Reach + playerLocation;

	DrawDebugLine
	(
		GetWorld(),
		playerLocation,
		lineTraceEnding,
		FColor::Red,
		false,
		0.f,
		0,
		5.f
	);

	FHitResult hit;
	if (GetWorld()->LineTraceSingleByObjectType(
		hit,
		playerLocation,
		lineTraceEnding,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
	))
	{
		UE_LOG(LogTemp, Warning, TEXT("Raycast hit an object: %s"), *hit.Actor->GetName());
	}
}

