// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_UseBaseSkillOnTarget.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AAEnemyPawn.h"
#include "AAPawn.h"
#include "AAIController.h"

EBTNodeResult::Type UBTTask_UseBaseSkillOnTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAAIController * AIController = Cast<AAAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		AAAEnemyPawn * Pawn = Cast<AAAEnemyPawn>(AIController->GetPawn());
		AAAPawn * Target = Cast<AAAPawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(AIController->TargetKeyID));
		if (Pawn && Target)
		{
			FVector Direction = Target->GetActorLocation() - Pawn->GetActorLocation();
			Direction.Normalize();
			Pawn->SetActorRotation(Direction.Rotation());
			Pawn->UseBaseSkill();
		}
	}

	return EBTNodeResult::Succeeded;
}


