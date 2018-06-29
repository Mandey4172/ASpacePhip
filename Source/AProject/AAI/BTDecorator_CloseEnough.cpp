// Fill out your copyright notice in the Description page of Project Settings.

#include "BTDecorator_CloseEnough.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AAIController.h"

UBTDecorator_CloseEnough::UBTDecorator_CloseEnough()
{
	Distance = 100.f;
}

bool UBTDecorator_CloseEnough::CalculateRawConditionValue(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) const
{
	AAAIController * AIController = Cast<AAAIController>(OwnerComp.GetAIOwner());
	if (AIController && AIController->GetPawn())
	{
		FVector AIPawnLocation = AIController->GetPawn()->GetActorLocation();
		FVector MoveLocation;
		
		AActor * Actor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID()));
		if (Actor)
		{
			MoveLocation = Actor->GetActorLocation();
		}
		else
		{
			MoveLocation = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
		}
		AIPawnLocation.Z = 0.f;
		MoveLocation.Z = 0.f;
		FVector Result = AIPawnLocation - MoveLocation;
		if (Result.Size() <= Distance)
		{
			return true;
		}
	}
	return false;
}
