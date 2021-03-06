// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UParticleSystem;
class USoundBase;

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
private:
	//Components
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ShootParticles;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ShootSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* HitSound;

	//Variables
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere)
	float Damage = 10.f;

	UPROPERTY(EditAnywhere)
	float DelayBetweenShots = 1.f;

	float ShotTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int Ammo = 30;

	//Functions
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

	float GetShotDelay() { return DelayBetweenShots; }

	void AddAmmo(int AmmoAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
