// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/Actor.h"
#include "ASkill.generated.h"

UCLASS()
class APROJECT_API AASkill : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASkill();

	UFUNCTION(BlueprintCallable)
	void Use(class AAAPawn * Pawn);

	// Called every frame
	//virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	virtual bool OnUse(class AAAPawn * Pawn);

	UPROPERTY(EditAnywhere)
	float SkillDelay;

private:	
	
	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle Timer_SkillDelay;

	void StartTimer(class AAAPawn * Pawn = nullptr);

	void ResetTimer();

	bool bCanUseSkill;
	
	static float GlobalColdown;
};
