// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:
	void CheckTargetInRange();

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire", meta = (AllowPrivateAccess = "true"))
	float FireRate = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire", meta = (AllowPrivateAccess = "true"))
	float FireRange = 1000.f;

	class APawnTank* PawnTank;

public:
	APawnTurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Destruction() override;
};
