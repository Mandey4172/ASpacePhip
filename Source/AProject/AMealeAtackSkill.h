// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "ASkill.h"
#include "AMealeAtackSkill.generated.h"

/**
 * 
 */
UCLASS()
class APROJECT_API AAMealeAtackSkill : public AASkill
{
	GENERATED_BODY()

public:

	AAMealeAtackSkill();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AAMealeStrike> BaseProjectile;

protected:

	UFUNCTION(BlueprintCallable)
	virtual bool OnUse(class AAAPawn * Pawn);

	UPROPERTY(EditAnywhere)
	FVector SkillOffset;
};
