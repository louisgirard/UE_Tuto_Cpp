// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

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
	class UParticleSystem* ShootParticles;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* HitParticles;

	//Variables
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;

public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
