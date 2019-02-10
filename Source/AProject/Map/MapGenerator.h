// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Map/MapTileType.h"
#include "MapGenerator.generated.h"

UCLASS()
class APROJECT_API AMapGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TArray<AMapTileType *> TilesInstances;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Generate();

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AMapTileType>> Tiles;

	UPROPERTY(EditAnywhere)
	float MaxX;
	UPROPERTY(EditAnywhere)
	float MaxY;
	UPROPERTY(EditAnywhere)
	float TileSize;
};
