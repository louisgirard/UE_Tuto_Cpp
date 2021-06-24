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
	
	ShotTimer = DelayBetweenShots;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ShotTimer += DeltaTime;
}

void AGun::PullTrigger()
{
	if (ShotTimer < DelayBetweenShots || Ammo == 0) return;
	ShotTimer = 0;
	Ammo = FMath::Clamp(Ammo - 1, 0, 100);

	UGameplayStatics::SpawnEmitterAttached(ShootParticles, GunMesh, "MuzzleFlashSocket");
	UGameplayStatics::SpawnSoundAttached(ShootSound, GunMesh, "MuzzleFlashSocket");

	FHitResult hit;
	FVector shotDirection;
	if (GunTrace(hit, shotDirection))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, hit.Location, shotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, hit.Location);

		if (hit.GetActor())
		{
			FPointDamageEvent damageEvent(Damage, hit, shotDirection, nullptr);
			hit.GetActor()->TakeDamage(Damage, damageEvent, GetOwner()->GetInstigatorController(), this);
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	FVector cameraLocation;
	FRotator cameraRotation;
	AController* playerController = GetOwner()->GetInstigatorController();

	if (!playerController) return false;

	playerController->GetPlayerViewPoint(cameraLocation, cameraRotation);
	ShotDirection = -cameraRotation.Vector();

	FVector endPoint = cameraLocation + cameraRotation.Vector() * MaxRange;

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(Hit, cameraLocation, endPoint, ECollisionChannel::ECC_GameTraceChannel1, params);
}

void AGun::AddAmmo(int AmmoAmount)
{
	Ammo += AmmoAmount;
}