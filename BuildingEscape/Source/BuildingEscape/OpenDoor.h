// Copyright, UE4 tutorial 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void MoveDoor(float deltaTime, float targetYaw);

	UPROPERTY(EditAnywhere)
	float TargetYaw = -90.0f;

	UPROPERTY(EditAnywhere)
	float OpeningSpeed = 45.0f;

	UPROPERTY(EditAnywhere)
	class ATriggerVolume* PressurePlate;

	FRotator StartingRotation;

};
