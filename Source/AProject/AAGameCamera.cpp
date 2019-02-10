// Fill out your copyright notice in the Description page of Project Settings.

#include "AAGameCamera.h"
#define xprint(text) print(text) 

 

AAAGameCamera::AAAGameCamera()
{
	MaximalInclination = 100.f;
	Inclination = 0.f;
	DeltaInclination = 10.f;
	DirectionChangeStrenght = 10.f;
	LastOwnerPosition = FVector::ZeroVector;
}

void AAAGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AActor * Owner = GetOwner();
	if (Owner)
	{
		FVector Movement = Owner->GetActorLocation() - LastOwnerPosition;
		if (Movement.Size() > 1.f)
		{
			if (Inclination < MaximalInclination)
				Inclination += DeltaTime * FMath::Abs(DeltaInclination);
		}
		else
		{
			if(Inclination > 0)
				Inclination -= DeltaTime * FMath::Abs(DeltaInclination);
		}
		InclinationVector += DirectionChangeStrenght * Owner->GetActorRotation().Vector();
		InclinationVector = InclinationVector.GetClampedToMaxSize(Inclination);
		FVector Location = Owner->GetActorLocation() + GetOffset() + InclinationVector;
		LastOwnerPosition = Owner->GetActorLocation();

#if !UE_BUILD_SHIPPING
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, InclinationVector.ToString());
#endif
		SetActorLocation(Location);
	}
}
