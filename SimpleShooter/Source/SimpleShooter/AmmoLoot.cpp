// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoLoot.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "ShooterCharacter.h"
#include "Gun.h"

// Sets default values
AAmmoLoot::AAmmoLoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");

	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>("AmmoMesh");
	AmmoMesh->SetupAttachment(BoxCollision);
}

// Called when the game starts or when spawned
void AAmmoLoot::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoLoot::AmmoOverlap);
}

// Called every frame
void AAmmoLoot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAmmoLoot::AmmoOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterCharacter* shooter = Cast<AShooterCharacter>(OtherActor);
	if (!shooter) return;

	shooter->AddAmmo(AmmoAmount, AmmoType);

	Destroy();
}

