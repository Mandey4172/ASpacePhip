// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/Actor.h"
#include "AProjectile.generated.h"

UCLASS()
class APROJECT_API AAProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual	void BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual	void EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintCallable)
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable)
	AAAPawn * GetProjectileOwner();

	UFUNCTION(BlueprintCallable)
	void SetProjectileOwner(AAAPawn * ProjectileOwner);

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SquareCollisionComponent;

	///* Projectile sprite component */
	UPROPERTY(VisibleAnywhere)
	class UPaperFlipbookComponent* ProjectileSprite;

	/* Projectile movement component */
	UPROPERTY(VisibleAnywhere)
	class UProjectileMovementComponent* ProjectileMovement;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	bool bDestroyOnOverlap;

	UPROPERTY(EditAnywhere)
	float Distance;

private:

	UPROPERTY(VisibleAnywhere)
	AAAPawn * ProjectileOwner;

};
