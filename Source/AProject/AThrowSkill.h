// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "ASkill.h"
#include "AThrowSkill.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AAThrowSkill : public AASkill
{
	GENERATED_BODY()
	
public:

	AAThrowSkill();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAAProjectile> BaseProjectile;

protected:

	bool OnUse(class AAAPawn * Pawn) override;

	UPROPERTY(EditAnywhere)
	FVector SkillOffset;

private:

};
