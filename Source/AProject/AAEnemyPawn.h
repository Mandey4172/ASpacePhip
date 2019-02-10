// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "AAPawn.h"
#include "AAEnemyPawn.generated.h"

UCLASS()
class APROJECT_API AAAEnemyPawn : public AAAPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAAEnemyPawn();

	// Called every frame
	void Tick(float DeltaTime) override;

	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	FVector GetFireDirection() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere)
	class UBehaviorTree * BehaviorTreeAsset;

	UPROPERTY(EditAnywhere)
	class UBlackboardData * BlackboardAsset;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UFloatingPawnMovement * PawnMovement;
};
