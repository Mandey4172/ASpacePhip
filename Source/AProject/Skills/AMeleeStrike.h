// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "AAPawn.h"
#include "GameFramework/Actor.h"
#include "Skills/ADamageable.h"
#include "AMeleeStrike.generated.h"

UCLASS()
class APROJECT_API AAMeleeStrike : public AActor, public IADamageable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMeleeStrike();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Collision component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	UBoxComponent * BoxCollisionComponent;

	/* Collision component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	USphereComponent * SphereCollisionComponent;

	UFUNCTION(BlueprintCallable)
	float GetDamage() override;

	void DealDamage(AAAPawn * TakingDamagePawn) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BeginOverlapSphere(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable)
	void EndOverlapSphere(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	void BeginOverlapBox(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	void EndOverlapBox(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintCallable)
	virtual	void BeginOverlap(class UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable)
	virtual	void EndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	float Damage;

private:

	bool bSphereOverleaping;
	bool bBoxOverlaping;
	bool bOverlaping;
};
