// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_CloseEnough.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API UBTDecorator_CloseEnough : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

	UBTDecorator_CloseEnough();

protected:	

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere)
	float Distance;
	
};
