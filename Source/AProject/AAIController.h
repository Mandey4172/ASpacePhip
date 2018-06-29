// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "AIController.h"
#include "AAIController.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AAAIController : public AAIController
{
	GENERATED_BODY()
public:

	AAAIController(const class FObjectInitializer& ObjectInitializer );

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UBlackboardComponent * BlackboardComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	class UBehaviorTreeComponent * BehaviorTreeComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	uint8 TargetKeyID;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	uint8 MoveLocationKeyID;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	uint8 NotifyRangeKeyID;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	uint8 MinimalDistanceID;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/* Called whenever the controller possesses a character bot */
	virtual void Possess(class APawn* InPawn) override;

	virtual void UnPossess() override;
};
