// Fill out your copyright notice in the Description page of Project Settings.

#include "AMealeAtackSkill.h"
#include "AAPawn.h"
#include"AMealeStrike.h"

AAMealeAtackSkill::AAMealeAtackSkill()
{
	BaseProjectile = AAMealeStrike::StaticClass();
}

bool AAMealeAtackSkill::OnUse(AAAPawn * Pawn)
{
	UWorld* const World = GetWorld();
	if (World && Pawn)
	{
		const FRotator FireRotation = Pawn->GetFireDirection().Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = Pawn->GetActorLocation() + FireRotation.RotateVector(SkillOffset);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Pawn;
		// spawn the projectile
		AAMealeStrike * Strike = World->SpawnActor<AAMealeStrike>(BaseProjectile, SpawnLocation, FireRotation, SpawnParams);
		if (Strike)
		{
			//Strike->SetSkillOwner(Pawn);
			return true;
		}
	}
	return false;
}
