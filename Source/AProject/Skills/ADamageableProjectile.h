// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skills/AProjectile.h"
#include "Skills/ADamageable.h"
#include "ADamageableProjectile.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AADamageableProjectile : public AAProjectile, public IADamageable
{
	GENERATED_BODY()
	
public:

	AADamageableProjectile();
	
	UFUNCTION(BlueprintCallable)
	float GetDamage() override;

	void DealDamage(class AAAPawn * TakingDamagePawn) override;

	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

protected:

	UPROPERTY(EditAnywhere)
	float Damage;
	
};
