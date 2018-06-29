// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "AAProjectile.generated.h"

UCLASS()
class APROJECT_API AAAProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAAProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	/** Returns ProjectileMesh subobject **/
	UStaticMeshComponent* GetProjectileMesh() const { return ProjectileMesh; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	UFUNCTION(BlueprintCallable)
	float GetDamage();

	UFUNCTION(BlueprintCallable)
	float GetDelay();

	UFUNCTION(BlueprintCallable)
	AAAPawn * GetProjectileOwner();

	UFUNCTION(BlueprintCallable)
	void SetProjectileOwner(AAAPawn * ProjectileOwner);

protected:

	UPROPERTY(EditAnywhere)
	bool bDestroyOnOverlap;

	UPROPERTY(EditAnywhere)
	float Damage;

	UPROPERTY(EditAnywhere)
	float UseDelay;

private:

	UPROPERTY(EditAnywhere)
	AAAPawn * ProjectileOwner;

	/** Sphere collision component */
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovement;
};
