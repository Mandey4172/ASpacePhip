// Fill out your copyright notice in the Description page of Project Settings.

#include "MapGenerator.h"


// Sets default values
AMapGenerator::AMapGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	MaxX = 100.f;
	MaxY = 100.f;
	TileSize = 64;
}

// Called when the game starts or when spawned
void AMapGenerator::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (Tiles.Num() > 0 && World)
	{
		// Generate Tile Types Instances
		for (TSubclassOf<AMapTileType> TileType : Tiles)
		{
			const FRotator & SpawnRotation = this->GetActorRotation();
			// Spawn projectile at an offset from this pawn
			const FVector & SpawnLocation = this->GetActorLocation();
			const FActorSpawnParameters SpawnParams;

			AMapTileType * TInstance = World->SpawnActor<AMapTileType>(TileType, SpawnLocation, SpawnRotation, SpawnParams);
			TilesInstances.Add(TInstance);
		}
		// Generate Tiles
		for (int i = 0; i < MaxX; i++)
		{
			for (int j = 0; j < MaxY; j++)
			{
				int r = FMath::RandRange(0, Tiles.Num() - 1);
				FVector Translation(i * TileSize, j * TileSize, 0);
				TilesInstances[r]->AddTile(Translation);
			}
		}
	}
}

// Called every frame
void AMapGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapGenerator::Generate()
{

}

