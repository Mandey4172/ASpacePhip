// Fill out your copyright notice in the Description page of Project Settings.

#include "AAPlayerController.h"
#include "AACamera.h"
#include "Engine.h"

AAAPlayerController::AAAPlayerController()
{
	CameraClass = AAACamera::StaticClass();
}

void AAAPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAAPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UWorld* const World = GetWorld();
	if (World)
	{
		FVector Location = FVector::ZeroVector;
		FRotator Rotation = FRotator::ZeroRotator;
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;

		Camera = World->SpawnActor<AAACamera>(CameraClass, Location, Rotation, SpawnParams);
		check(GetPawn());
		APawn * Pawn = GetPawn();
		if (Camera && Pawn)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT(":D :D :D "));
			Camera->SetUp(Pawn);
			SetViewTarget(Camera);
		}
	}
}

AAACamera * AAAPlayerController::GetCamera()
{
	return Camera;
}
