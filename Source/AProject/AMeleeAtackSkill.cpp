// Fill out your copyright notice in the Description page of Project Settings.

#include "AMeleeAtackSkill.h"
#include "AAPawn.h"
#include "AMeleeStrike.h"

AAMeleeAtackSkill::AAMeleeAtackSkill()
{
	BaseProjectile = AAMeleeStrike::StaticClass();
}

bool AAMeleeAtackSkill::OnUse(AAAPawn * Pawn)
{
	UWorld* const World = GetWorld();
	if (World && Pawn)
	{
		const FRotator FireRotation = Pawn->GetFireDirection().Rotation();
		// Spawn projectile at an offset from this pawn
		const FVector SpawnLocation = Pawn->GetActorLocation() + FireRotation.RotateVector(SkillOffset);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = Pawn;
		SpawnParams.Instigator = Pawn;
		// spawn the projectile
		AAMeleeStrike * Strike = World->SpawnActor<AAMeleeStrike>(BaseProjectile, SpawnLocation, FireRotation, SpawnParams);
		if (Strike)
		{
			//Strike->SetSkillOwner(Pawn);
			return true;
		}
	}
	return false;
}
