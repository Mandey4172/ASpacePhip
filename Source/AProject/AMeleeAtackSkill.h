// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "ASkill.h"
#include "AMeleeAtackSkill.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AAMeleeAtackSkill : public AASkill
{
	GENERATED_BODY()

public:

	AAMeleeAtackSkill();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAMeleeStrike> BaseProjectile;

protected:

	virtual bool OnUse(class AAAPawn * Pawn) override;

	UPROPERTY(EditAnywhere)
	FVector SkillOffset;
};
