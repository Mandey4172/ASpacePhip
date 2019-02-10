// Fill out your copyright notice in the Description page of Project Settings.

#include "ADamageableProjectile.h"
#include "AAPawn.h"

AADamageableProjectile::AADamageableProjectile()
{
	Damage = 1.f;
}


float AADamageableProjectile::GetDamage()
{
	return Damage;
}

void AADamageableProjectile::DealDamage(AAAPawn * TakingDamagePawn)
{
	if (TakingDamagePawn)
	{
		FDamageEvent DamageEvent;
		TakingDamagePawn->TakeDamage(GetDamage(), DamageEvent, GetInstigatorController(), GetInstigator());
	}
}

void AADamageableProjectile::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	DealDamage(Cast<AAAPawn>(OtherActor));
	if (bDestroyOnOverlap) Destroy();
}

void AADamageableProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DealDamage(Cast<AAAPawn>(OtherActor));
	Destroy();
}


