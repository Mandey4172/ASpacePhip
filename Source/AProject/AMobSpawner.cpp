// Fill out your copyright notice in the Description page of Project Settings.

#include "AMobSpawner.h"
#include "AAEnemyPawn.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AAMobSpawner::AAMobSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area"));

	ActorToSpawn = AAAEnemyPawn::StaticClass();

	SpawnDelayRangeLow = 1.f;
	SpawnDelayRangeHigh = 4.f;
	
	NumberOfSpawns = 0;
	SpawnsCounter = 0;
}

// Called when the game starts or when spawned
void AAMobSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
	GetWorldTimerManager().SetTimer(SpawnTimer, this, &AAMobSpawner::SpawnPickup, SpawnDelay, false);

}

void AAMobSpawner::SpawnPickup()
{
	UWorld * const World = GetWorld();
	if (ActorToSpawn && World)
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = this;
		SpawnParam.Instigator = Instigator;

		FVector SpawnLocation = GetRandomPointInVolume();
		FRotator SpawnRotation = FRotator::ZeroRotator;
		SpawnRotation.Yaw = FMath::Rand() * 360.f;
		
		World->SpawnActor<AActor>(ActorToSpawn, SpawnLocation, SpawnRotation, SpawnParam);
		SpawnsCounter++;
	}
	if ((NumberOfSpawns == 0) || (SpawnsCounter < NumberOfSpawns))
	{
		SpawnDelay = FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
		GetWorldTimerManager().SetTimer(SpawnTimer, this, &AAMobSpawner::SpawnPickup, SpawnDelay, false);
	}
}

// Called every frame
void AAMobSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent * AAMobSpawner::GetSpawnArea()
{
	return SpawnArea;
}

FVector AAMobSpawner::GetRandomPointInVolume()
{

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnArea->Bounds.Origin, SpawnArea->Bounds.BoxExtent);
}

