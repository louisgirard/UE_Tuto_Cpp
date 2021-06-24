// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/World.h"
#include "Gun.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	SpawnWeapons();

	CurrentHealth = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AShooterCharacter::Fire);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AShooterCharacter::Jump);
	PlayerInputComponent->BindAction("ChangeWeaponUp", IE_Pressed, this, &AShooterCharacter::ChangeWeaponUp);
	PlayerInputComponent->BindAction("ChangeWeaponDown", IE_Pressed, this, &AShooterCharacter::ChangeWeaponDown);
}

void AShooterCharacter::SpawnWeapons()
{
	GetMesh()->HideBoneByName("weapon_r", EPhysBodyOp::PBO_None);

	for (int i = 0; i < GunTypes.Num(); i++)
	{
		AGun* gun = GetWorld()->SpawnActor<AGun>(GunTypes[i]);
		gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
		gun->SetOwner(this);
		gun->SetActorHiddenInGame(true);
		Guns.Add(gun);
	}

	Guns[0]->SetActorHiddenInGame(false);
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::Fire()
{
	Guns[CurrentGunIndex]->PullTrigger();
}

void AShooterCharacter::ChangeWeaponUp()
{
	Guns[CurrentGunIndex]->SetActorHiddenInGame(true);
	CurrentGunIndex = (CurrentGunIndex + 1) % Guns.Num();
	Guns[CurrentGunIndex]->SetActorHiddenInGame(false);
}

void AShooterCharacter::ChangeWeaponDown()
{
	Guns[CurrentGunIndex]->SetActorHiddenInGame(true);
	CurrentGunIndex--;
	if (CurrentGunIndex < 0)
	{
		CurrentGunIndex = Guns.Num() - 1;
	}
	Guns[CurrentGunIndex]->SetActorHiddenInGame(false);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float damageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	damageToApply = FMath::Min(CurrentHealth, damageToApply);
	CurrentHealth -= damageToApply;

	if (IsDead())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ASimpleShooterGameModeBase* gameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (gameMode)
		{
			gameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
	}

	return damageToApply;
}

