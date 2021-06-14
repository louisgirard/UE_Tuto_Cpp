// Copyright, UE4 tutorial 2021


#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle missing on %s"), *GetOwner()->GetName());
	}

	GetOwner()->InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	GetOwner()->InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->SetTargetLocation(GetLineTraceEnd());
	}
}

void UGrabber::Grab()
{
	FHitResult hitResult = GetPhysicsBodyInReach();
	if (hitResult.GetActor() == nullptr) return;

	PhysicsHandle->GrabComponentAtLocation(
		hitResult.GetComponent(),
		NAME_None,
		GetLineTraceEnd()
	);
}

void UGrabber::Release()
{
	if (PhysicsHandle->GetGrabbedComponent())
	{
		UE_LOG(LogTemp, Warning, TEXT("Release object"));
		PhysicsHandle->ReleaseComponent();
	}
}

FHitResult UGrabber::GetPhysicsBodyInReach()
{
	FVector playerLocation;
	FRotator playerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotation);

	FHitResult hit;
	if (GetWorld()->LineTraceSingleByObjectType(
		hit,
		playerLocation,
		GetLineTraceEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)
	))
	{
		UE_LOG(LogTemp, Warning, TEXT("Grab object: %s"), *hit.GetActor()->GetName());
	}
	return hit;
}

FVector UGrabber::GetLineTraceEnd()
{
	FVector playerLocation;
	FRotator playerRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(playerLocation, playerRotation);

	return playerRotation.Vector() * Reach + playerLocation;
}

