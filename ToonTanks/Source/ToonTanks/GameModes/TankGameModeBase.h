// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"


UCLASS()
class TOONTANKS_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	class APawnTank* PlayerTank;
	int NumberOfTurrets = 0;
	class APlayerControllerBase* PlayerController;

	void HandleGameStart();
	void HandleGameOver(bool playerWon);

public:
	void ActorDied(AActor* deadActor);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Loop")
	int32 CountdownDelay = 3;

	virtual void BeginPlay() override;
		
	UFUNCTION(BlueprintImplementableEvent)
	void GameStart();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool playerWon);

};
