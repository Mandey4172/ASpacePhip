// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_FindNewLocationInRange.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "AAPawn.h"
#include "AAIController.h"

UBTTask_FindNewLocationInRange::UBTTask_FindNewLocationInRange()
{
	Distance = 10000.f;
}

EBTNodeResult::Type UBTTask_FindNewLocationInRange::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAAIController * AIController = Cast<AAAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		UWorld * const World = AIController->GetWorld();
		//FVector MoveLocation =  World->GetNavigationSystem()->GetRandomReachablePointInRadius(World,;
		FVector Orgin = AIController->GetPawn()->GetActorLocation();
		FNavLocation Output;
		if (FNavigationSystem::GetCurrent<UNavigationSystemV1>(World)->GetRandomReachablePointInRadius(Orgin, Distance, Output, nullptr, nullptr))
		{
			FVector MoveLocation = Output.Location;
			MoveLocation.Z = 0;
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(AIController->MoveLocationKeyID, MoveLocation);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
