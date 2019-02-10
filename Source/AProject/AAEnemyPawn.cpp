// Fill out your copyright notice in the Description page of Project Settings.

#include "AAEnemyPawn.h"
#include "AAPlayerPawn.h"
#include "Skills/ADamageable.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Runtime/Engine/Classes/GameFramework/FloatingPawnMovement.h"

// Sets default values
AAAEnemyPawn::AAAEnemyPawn()
{
	BlackboardAsset = NewObject<UBlackboardData>();
	BehaviorTreeAsset = NewObject<UBehaviorTree>();
	BehaviorTreeAsset->BlackboardAsset = BlackboardAsset;
	
	PawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Pawn Movement"));
	PawnMovement->MaxSpeed = 900;
	PawnMovement->Acceleration = 900;
	PawnMovement->Deceleration = 4000;

	BoxCollisionComponent->SetSimulatePhysics(true);
	BoxCollisionComponent->SetLinearDamping(100000.f);
	BoxCollisionComponent->SetAngularDamping(100000.f);
}

// Called when the game starts or when spawned
void AAAEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAAEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAAEnemyPawn::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//IADamageable * Damageable = Cast<IADamageable>(OtherActor);
	//if (Damageable)
	//{
	//	AAAPlayerPawn * Player = Cast<AAAPlayerPawn>(OtherActor->GetInstigator());
	//	if (Player)
	//	{
	//		FDamageEvent DamageEvent;
	//		TakeDamage(Damageable->GetDamage(), DamageEvent, nullptr, Player);
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EnemyPawn::TakeDmage!"));
	//	}
	//}
}

void AAAEnemyPawn::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//IADamageable * Damageable = Cast<IADamageable>(OtherActor);
	//if (Damageable)
	//{
	//	AAAPlayerPawn * Player = Cast<AAAPlayerPawn>(OtherActor->GetInstigator());
	//	if (Player)
	//	{
	//		FDamageEvent DamageEvent;
	//		TakeDamage(Damageable->GetDamage(), DamageEvent, nullptr, Player);
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EnemyPawn::TakeDmage!"));
	//	}
	//}
}

float AAAEnemyPawn::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	AAAPlayerPawn * Player = Cast<AAAPlayerPawn>(DamageCauser);
	if (Player)
	{
		AAAPawn::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Ememy Pawn HP: %f"), this->GetHealth()));
	}
	return 0.f;
}

FVector AAAEnemyPawn::GetFireDirection()
{
	return GetActorRotation().Vector();
}