// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_FindNewLocationInRange.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UBTTask_FindNewLocationInRange : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:

	UBTTask_FindNewLocationInRange();

	virtual EBTNodeResult::Type ExecuteTask(class UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

	UPROPERTY(EditAnywhere)
	float Distance;

};
