// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_CheckForTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AAPawn.h"
#include "AAIController.h"

UBTService_CheckForTarget::UBTService_CheckForTarget()
{
	bCreateNodeInstance = true;
	NotyfyDistange = 500;
}

void UBTService_CheckForTarget::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	AAAIController * AIController = Cast<AAAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AAAPawn * Pawn = Cast<AAAPawn>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (Pawn)
		{
			FVector Dif = Pawn->GetActorLocation() - AIController->GetPawn()->GetActorLocation();
			//float NotyfyDistange = OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Float>(AIController->NotifyRangeKeyID);
			if (Dif.Size() <= NotyfyDistange)
			{
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(AIController->TargetKeyID, Pawn);
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(AIController->TargetKeyID, nullptr);
			}
		}
	}
}