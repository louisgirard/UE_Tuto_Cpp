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
	void OpenDoor(float deltaTime);
	void CloseDoor(float deltaTime);
	bool MassReached();

	UPROPERTY(EditAnywhere)
	float TargetYaw = -90.0f;

	UPROPERTY(EditAnywhere)
	float OpeningSpeed = 45.0f;

	UPROPERTY(EditAnywhere)
	float ClosingSpeed = 80.0f;

	UPROPERTY(EditAnywhere)
	class ATriggerVolume* PressurePlate;

	FRotator StartingRotation;

	float DoorLastOpened = 0.f;
	bool OpenSoundPlayed = false;
	bool CloseSoundPlayed = true;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 2.f;

	UPROPERTY(EditAnywhere)
	float MassRequired = 20.f;

	class UAudioComponent* DoorAudio = nullptr;
};
