// Fill out your copyright notice in the Description page of Project Settings.

#include "ASkill.h"
#include "AAPawn.h"

// Sets default values
AASkill::AASkill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SkillDelay = 1.f;
	bCanUseSkill = true;
}

// Called when the game starts or when spawned
void AASkill::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AASkill::OnUse(AAAPawn * Pawn)
{
	return true;
}


void AASkill::StartTimer(AAAPawn * Pawn)
{
	UWorld* const World = GetWorld();
	if (World && Pawn)
	{
		bCanUseSkill = false;
		float ActualDelay = SkillDelay * Pawn->GetSkillRate();
		if (ActualDelay < 0.f) ActualDelay = 1.f;
		World->GetTimerManager().SetTimer(Timer_SkillDelay, this, &AASkill::ResetTimer, ActualDelay);
	}
}

void AASkill::ResetTimer()
{
	bCanUseSkill = true;
}

void AASkill::Use(AAAPawn * Pawn)
{
	UWorld* const World = GetWorld();
	if (World && bCanUseSkill)
	{
		if (OnUse(Pawn))
		{
			StartTimer(Pawn);
		}
	}
	
}

// Called every frame
void AASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

