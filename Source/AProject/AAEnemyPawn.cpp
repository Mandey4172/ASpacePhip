// Fill out your copyright notice in the Description page of Project Settings.

#include "AAEnemyPawn.h"
#include "AAPlayerPawn.h"
#include "AAProjectile.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Runtime/Engine/Classes/GameFramework/FloatingPawnMovement.h"

// Sets default values
AAAEnemyPawn::AAAEnemyPawn()
{
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement"));

	BoxCollisionComponent->SetSimulatePhysics(true);
	BoxCollisionComponent->SetLockedAxis(EDOFMode::XYPlane);

	BlackboardAsset = NewObject<UBlackboardData>();
	BehaviorTreeAsset = NewObject<UBehaviorTree>();
	BehaviorTreeAsset->BlackboardAsset = BlackboardAsset;
	//PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement"));
}

// Called when the game starts or when spawned
void AAAEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAAEnemyPawn::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAAProjectile * Projectile = Cast<AAAProjectile>(OtherActor);
	if (Projectile)
	{
		if (GetOwner() && (GetOwner()->GetClass() == AAAPlayerPawn::StaticClass()))
		{
			FDamageEvent DamageEvent;
			TakeDamage(Projectile->GetDamage(), DamageEvent, nullptr, Projectile->GetOwner());
		}
	}
}

void AAAEnemyPawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AAAProjectile * Projectile = Cast<AAAProjectile>(OtherActor);
	if (Projectile)
	{
		AAAPlayerPawn * Player = Cast<AAAPlayerPawn>(Projectile->GetInstigator());
		if (Player)
		{
			FDamageEvent DamageEvent;
			TakeDamage(Projectile->GetDamage(), DamageEvent, nullptr, Projectile->GetOwner());
		}
	}
}

// Called every frame
void AAAEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

