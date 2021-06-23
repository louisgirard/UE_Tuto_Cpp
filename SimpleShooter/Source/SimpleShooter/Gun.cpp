// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunMesh");

	GunMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(ShootParticles, GunMesh, "MuzzleFlashSocket");

	FVector cameraLocation;
	FRotator cameraRotation;
	AController* playerController = GetOwner()->GetInstigatorController();
	playerController->GetPlayerViewPoint(cameraLocation, cameraRotation);

	FVector endPoint = cameraLocation + cameraRotation.Vector() * MaxRange;

	FHitResult hit;
	if (GetWorld()->LineTraceSingleByChannel(hit, cameraLocation, endPoint, ECollisionChannel::ECC_GameTraceChannel1))
	{
		FVector shotDirection = -cameraRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, hit.Location, shotDirection.Rotation());

		if (hit.GetActor())
		{
			FPointDamageEvent damageEvent(Damage, hit, shotDirection, nullptr);
			hit.GetActor()->TakeDamage(Damage, damageEvent, playerController, this);
		}
	}

}
