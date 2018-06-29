// Fill out your copyright notice in the Description page of Project Settings.


#include "AACamera.h"
#include "Engine.h"

AAACamera::AAACamera()
{
	Offset = FVector(0.f, 0.f, 200.f);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.SetTickFunctionEnable(true);
}

void AAACamera::SetOffset(FVector NOffset)
{
	Offset = NOffset;
}

void AAACamera::BeginPlay()
{
	Super::BeginPlay();
}

void AAACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AActor * Owner = GetOwner();
	if (Owner)
	{
		SetActorLocation(Owner->GetActorLocation() + Offset);
	}
}

void AAACamera::SetUp(APawn * CameraOwner)
{
	if (CameraOwner)
	{
		SetOwner(CameraOwner);
		PrimaryActorTick.AddPrerequisite(CameraOwner, CameraOwner->PrimaryActorTick);

		FVector Location = CameraOwner->GetActorLocation();
		Location += Offset;
		
		FVector Rotation = -Offset;
		Rotation.Normalize();

		SetActorLocation(Location);
		SetActorRotation(Rotation.Rotation());
	}
}


FVector AAACamera::GetOffset()
{
	return Offset;
}