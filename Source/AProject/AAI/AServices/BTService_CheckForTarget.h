// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckForTarget.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UBTService_CheckForTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:

	UBTService_CheckForTarget();
			
	virtual void TickNode(class UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds);

protected:
	UPROPERTY(EditAnywhere)
	float NotyfyDistange;
};
