// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Skills/ADamageable.h"
#include "AExplosion.generated.h"

UCLASS()
class APROJECT_API AAExplosion : public AActor, public IADamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAExplosion();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SquareCollisionComponent;

	///* Projectile sprite component */
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* ExplosionSprite;

	UFUNCTION(BlueprintCallable)
	float GetDamage() override;

	void DealDamage(class AAAPawn * TakingDamagePawn) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float Damage;
};
