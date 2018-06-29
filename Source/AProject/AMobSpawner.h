// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "AMobSpawner.generated.h"

UCLASS()
class APROJECT_API AAMobSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMobSpawner();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	class UBoxComponent * GetSpawnArea();

	UFUNCTION(BlueprintCallable)
	FVector GetRandomPointInVolume();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToSpawn;
	
	UPROPERTY(EditAnywhere)
	float SpawnDelayRangeLow;
	
	UPROPERTY(EditAnywhere)
	float SpawnDelayRangeHigh;

	UPROPERTY(EditAnywhere)
	int NumberOfSpawns;

	FTimerHandle SpawnTimer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent * SpawnArea;

private:
	
	float SpawnDelay;

	int SpawnsCounter;

	void SpawnPickup();
};
