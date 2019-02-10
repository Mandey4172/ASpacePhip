// Fill out your copyright notice in the Description page of Project Settings.

#include "AMeleeStrike.h"
#include "AAPlayerPawn.h"
#include "AAEnemyPawn.h"

// Sets default values
AAMeleeStrike::AAMeleeStrike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereCollisionComponent->InitSphereRadius(100.f);
	SphereCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAMeleeStrike::BeginOverlapSphere);
	SphereCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AAMeleeStrike::EndOverlapSphere);
	RootComponent = SphereCollisionComponent;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCollisionComponent->InitBoxExtent(FVector(50.f, 100.f, 100.f));
	BoxCollisionComponent->AddLocalOffset(FVector(50.f, 0.f, 0.f));
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAMeleeStrike::BeginOverlapBox);
	BoxCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AAMeleeStrike::EndOverlapBox);
	BoxCollisionComponent->AttachTo(GetRootComponent());
	
	InitialLifeSpan = 0.1f;
	bSphereOverleaping = false;
	bBoxOverlaping = false;
	bOverlaping = false;
}

float AAMeleeStrike::GetDamage()
{
	return Damage;
}

void AAMeleeStrike::DealDamage(AAAPawn * TakingDamagePawn)
{
	if (TakingDamagePawn)
	{
		FDamageEvent DamageEvent;
		TakingDamagePawn->TakeDamage(GetDamage(), DamageEvent, GetInstigatorController(), GetInstigator());
	}
}

// Called when the game starts or when spawned
void AAMeleeStrike::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAMeleeStrike::BeginOverlapSphere(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (BoxCollisionComponent->IsOverlappingActor(OtherActor))
	{
		bOverlaping = true;
		BeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,SweepResult);
	}
}

void AAMeleeStrike::EndOverlapSphere(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (BoxCollisionComponent->IsOverlappingActor(OtherActor))
	{
		EndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	}
}

void AAMeleeStrike::BeginOverlapBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (SphereCollisionComponent->IsOverlappingActor(OtherActor))
	{
		BeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void AAMeleeStrike::EndOverlapBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (SphereCollisionComponent->IsOverlappingActor(OtherActor))
	{
		EndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	}
}

void AAMeleeStrike::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	DealDamage(Cast<AAAPawn>(OtherActor));
	//if((OtherActor != this) && (GetInstigator() != OtherActor))
	//{
	//	Pawn->BeginOverlap(OtherComp, this, OverlappedComp, OtherBodyIndex, bFromSweep, SweepResult);
	//	/*AAAPlayerPawn * Player = Cast<AAAPlayerPawn>(OtherActor);*/
	//	AAAEnemyPawn * Enemy = Cast<AAAEnemyPawn>(GetInstigator());
	//	if (Player && Enemy)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Begin Overlap 1"));
	//	}
	//	Player = Cast<AAAPlayerPawn>(GetInstigator());
	//	Enemy = Cast<AAAEnemyPawn>(OtherActor);
	//	if (Player && Enemy)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Begin Overlap 2"));
	//		return;
	//	}
	//}
}

void AAMeleeStrike::EndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	//if ((OtherActor != this) && (GetInstigator() != OtherActor))
	//{
	//	AAAPlayerPawn * Player = Cast<AAAPlayerPawn>(OtherActor);
	//	AAAEnemyPawn * Enemy = Cast<AAAEnemyPawn>(GetInstigator());
	//	if (Player && Enemy)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Overlap 1"));
	//		return;
	//	}
	//	Player = Cast<AAAPlayerPawn>(GetInstigator());
	//	Enemy = Cast<AAAEnemyPawn>(OtherActor);
	//	if (Player && Enemy)
	//	{
	//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Overlap 2"));
	//		return;
	//	}
	//}
}

// Called every frame
void AAMeleeStrike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

