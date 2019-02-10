// Fill out your copyright notice in the Description page of Project Settings.

#include "AThrowSkill.h"
#include "AProjectile.h"
#include "AAPawn.h"

AAThrowSkill::AAThrowSkill()
{
	SkillDelay = 0.5f;
	SkillOffset = FVector(70.f, 0.f, 0.f);
	BaseProjectile = AAProjectile::StaticClass();
}

bool AAThrowSkill::OnUse(AAAPawn * Pawn)
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
		AAProjectile * Projectile = World->SpawnActor<AAProjectile>(BaseProjectile, SpawnLocation, FireRotation, SpawnParams);
		if (Projectile)
		{
			//Projectile->SetProjectileOwner(Pawn);
			return true;
		}
	}
	return false;
}
