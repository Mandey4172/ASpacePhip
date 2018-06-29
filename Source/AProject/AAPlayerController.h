// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "GameFramework/PlayerController.h"
#include "AAPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AAAPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AAAPlayerController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// 
	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAACamera> CameraClass;

	//
	UFUNCTION(BlueprintCallable)
	class AAACamera * GetCamera();

private:
	// 
	class AAACamera * Camera;
	
};
