// Fill out your copyright notice in the Description page of Project Settings.

#include "AExplodingProjectile.h"
#include "Skills/AExplosion.h"

AAExplodingProjectile::AAExplodingProjectile()
{
	ExposionType = AAExplosion::StaticClass();
}

//void AAExplodingProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExplosiveProjectile::BeginOverleap!"));
//}
//
//void AAExplodingProjectile::EndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExplosiveProjectile::EndOverleap!"));
//
//}

//void AAExplodingProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ExplosiveProjectile::OnHit!"));
//}

void AAExplodingProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UWorld * World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = GetInstigator();
		SpawnParameters.Owner = GetOwner();
		World->SpawnActor<AAExplosion>(ExposionType, GetActorLocation(), GetActorRotation(), SpawnParameters);
	}
}
