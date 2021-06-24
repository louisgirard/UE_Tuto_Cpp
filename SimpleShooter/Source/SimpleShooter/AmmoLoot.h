// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoLoot.generated.h"

UCLASS()
class SIMPLESHOOTER_API AAmmoLoot : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* AmmoMesh;

	UPROPERTY(EditAnywhere)
	int AmmoAmount = 10;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AGun> AmmoType;

	UFUNCTION()
	void AmmoOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Sets default values for this actor's properties
	AAmmoLoot();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
