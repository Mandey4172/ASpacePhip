// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "AACamera.h"
#include "AAGameCamera.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AAAGameCamera : public AAACamera
{
	GENERATED_BODY()

public:

	AAAGameCamera();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:

	UPROPERTY(EditAnywhere)
	float MaximalInclination;

	UPROPERTY(EditAnywhere)
	float DeltaInclination;

	UPROPERTY(EditAnywhere)
	float DirectionChangeStrenght;

private:

	float Inclination;
	
	FVector LastOwnerPosition;

	FVector InclinationVector;
};
