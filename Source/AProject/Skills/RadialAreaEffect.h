// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Skills/ADamageable.h"
#include "RadialAreaEffect.generated.h"

struct TickHandler
{
	AAAPawn * Pawn;
	float ElapsedTime;

	bool operator==(const TickHandler& rhs)
	{
		if (this->Pawn == rhs.Pawn) return true;
		return false;
	}
};

UCLASS()
class APROJECT_API ARadialAreaEffect : public AActor, public IADamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARadialAreaEffect();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual	void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	float GetDamage() override;

	void DealDamage(class AAAPawn * TakingDamagePawn) override;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SquareCollisionComponent;

	///* Projectile sprite component */
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* EffectSprite;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float DamagePerTick;

	UPROPERTY(EditAnywhere)
	float TickTime;

private:

	//float ElapsedTime;

	TArray<struct TickHandler> TickHandlers;
};

