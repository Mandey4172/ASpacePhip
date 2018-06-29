// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Camera/CameraActor.h"
#include "GameFramework/Pawn.h"
#include "AACamera.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AAACamera : public ACameraActor
{
	GENERATED_BODY()
	
public:

	AAACamera();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Bind camera
	UFUNCTION(BlueprintCallable)
    virtual void SetUp(APawn * CameraOwner);

	//Offset of camera
	UFUNCTION(BlueprintCallable)
	FVector GetOffset();
	UFUNCTION(BlueprintCallable)
	void	SetOffset(FVector Offset);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	FVector Offset;
};
