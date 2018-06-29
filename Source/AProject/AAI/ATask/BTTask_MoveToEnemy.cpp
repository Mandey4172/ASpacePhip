// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MoveToEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "AAPawn.h"
#include "AAIController.h"

UBTTask_MoveToEnemy::UBTTask_MoveToEnemy()
{
	Distance = 50.f;
}

EBTNodeResult::Type UBTTask_MoveToEnemy::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AAAIController * AIController = Cast<AAAIController>(OwnerComp.GetAIOwner());
	AAAPawn *Enemy = Cast<AAAPawn>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(AIController->TargetKeyID));
	if (Enemy)
	{
		AIController->MoveToActor(Enemy, Distance, true, true, false, 0, false);
		if (AIController->GetPawn())
		{
			FVector ADist = Enemy->GetActorLocation() - AIController->GetPawn()->GetActorLocation();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Size : %f Dif: %f"), ADist.Size(), Distance));
			if (ADist.Size() < Distance)
			{
				FVector Face = Enemy->GetActorLocation() - AIController->GetPawn()->GetActorLocation();
				Face.Z = 0;
				Face.Normalize();
				AIController->GetPawn()->SetActorRotation(Face.Rotation());
			}
		}
		return EBTNodeResult::Succeeded;
	}

	
	/*if (Enemy &&  AIController)
	{
		AIController->MoveToActor(Enemy, 5.f, true, true, true, 0, true);
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Moving");
		return EBTNodeResult::Succeeded;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, "Not moving");
	}*/
	return EBTNodeResult::Failed;
}
