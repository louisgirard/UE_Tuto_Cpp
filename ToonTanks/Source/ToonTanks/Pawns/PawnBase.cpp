// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>("CapsuleCollider");
	RootComponent = Capsule;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	BaseMesh->SetupAttachment(RootComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>("TurretMesh");
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>("ProjectileSpawnPoint");
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	Health = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

void APawnBase::RotateTurret(FVector target)
{
	target.Z = TurretMesh->GetComponentLocation().Z;
	FVector direction = target - TurretMesh->GetComponentLocation();

	TurretMesh->SetWorldRotation(direction.Rotation());
}

void APawnBase::Fire()
{
	// Fire projectile
	UE_LOG(LogTemp, Warning, TEXT("%s fired a projectile"), *GetName());

	if (!ProjectileClass) return;

	AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(
		ProjectileClass,
		ProjectileSpawnPoint->GetComponentLocation(),
		ProjectileSpawnPoint->GetComponentRotation());

	TempProjectile->SetOwner(this);
}

void APawnBase::Destruction()
{
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation());
	UGameplayStatics::PlaySoundAtLocation(this, DestructionSound, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(ExplosionShake);
}

