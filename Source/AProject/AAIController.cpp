// Fill out your copyright notice in the Description page of Project Settings.

#include "AAIController.h"
#include "AAEnemyPawn.h"
//#include "XBaseEnemyCharacter.h"
/* AI Specific includes */
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

AAAIController::AAAIController( const class FObjectInitializer& ObjectInitializer )
	: Super(ObjectInitializer)
{
	BehaviorTreeComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this,TEXT("Behavior Tree Component"));
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("Blackboard Component"));
}

void AAAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AAAIController::Possess(class APawn* InPawn)
{
	Super::Possess(InPawn);

	AAAEnemyPawn * AICharacter = Cast<AAAEnemyPawn>(InPawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTreeAsset)
		{
			if (AICharacter->BehaviorTreeAsset->BlackboardAsset)
			{
				BlackboardComp->InitializeBlackboard(*AICharacter->BehaviorTreeAsset->BlackboardAsset);
				TargetKeyID = BlackboardComp->GetKeyID("Target");
				MoveLocationKeyID = BlackboardComp->GetKeyID("MoveLocation");
				NotifyRangeKeyID = BlackboardComp->GetKeyID("NotifyRange");
				MinimalDistanceID = BlackboardComp->GetKeyID("MinimalDistance");
				
				BlackboardComp->SetValue<UBlackboardKeyType_Object>(BlackboardComp->GetKeyID("SelfActor"), AICharacter);
				BlackboardComp->SetValue<UBlackboardKeyType_Vector>(MoveLocationKeyID, AICharacter->GetActorLocation());
			}
			BehaviorTreeComp->StartTree(*AICharacter->BehaviorTreeAsset);
		}
	}
}

void AAAIController::UnPossess()
{
	Super::UnPossess();

	BehaviorTreeComp->StopTree();
}