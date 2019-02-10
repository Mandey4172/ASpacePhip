// Fill out your copyright notice in the Description page of Project Settings.

#include "ADamageable.h"
#include "AAPawn.h"

// Add default functionality here for any IADamageable functions that are not pure virtual.

float IADamageable::GetDamage()
{
	return 0.f;
}

void IADamageable::DealDamage(AAAPawn * TakingDamagePawn)
{

}
