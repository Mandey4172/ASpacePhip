// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "Skills/ASkill.h"
#include "GameFramework/Pawn.h"
#include "AAPawn.generated.h"


UCLASS()
class APROJECT_API AAAPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAAPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	virtual	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/* Fire a shot in the specified direction */
	UFUNCTION(BlueprintCallable)
	void UseBaseSkill();

	/* Handler for the fire timer expiry */
	UFUNCTION(BlueprintCallable)
	void FireTimerExpired();

	UFUNCTION(BlueprintCallable)
	float GetDamage();

	UFUNCTION(BlueprintCallable)
	float GetSkillRate();

	UFUNCTION(BlueprintCallable)
	float GetHealth();

	UFUNCTION(BlueprintCallable)
	virtual FVector GetFireDirection();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AASkill> BaseSkillClass;

	/* Sprite comonent */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UPaperFlipbookComponent* ActorSpriteComponent;

	/* Collision component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UBoxComponent * BoxCollisionComponent;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float MaxHealth;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(EditAnywhere)
	float SkillRate;

	UPROPERTY(EditAnywhere)
	float Damage;

private:
	
	float Health;

	bool bCanFire;

	class AASkill * BaseSkill;

	/** Handle for efficient management of ShotTimerExpired timer */
	FTimerHandle Timer_FireDelay;
};
