// Fill out your copyright notice in the Description page of Project Settings.

#include "AExplosion.h"
#include "PaperFlipbookComponent.h"
#include "AAPawn.h"

// Sets default values
AAExplosion::AAExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//
	//InitialRadius = 100.f;
	//MaximalRadius = 1000.f;
	Damage = 1.f;
	//
	SquareCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SquareCollisionComponent->SetSphereRadius(100.f);
	SquareCollisionComponent->SetupAttachment(RootComponent);
	SquareCollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	SquareCollisionComponent->OnComponentHit.AddDynamic(this, &AAExplosion::OnHit);
	SquareCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAExplosion::BeginOverlap);
	RootComponent = SquareCollisionComponent;

	// Create flipbook component for the projectile sphere
	ExplosionSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComponent"));
	ExplosionSprite->AttachTo(GetRootComponent());

	InitialLifeSpan = 1.f;
}

void AAExplosion::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	DealDamage(Cast<AAAPawn>(OtherActor));
}

void AAExplosion::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//DealDamage(Cast<AAAPawn>(OtherActor));
}

float AAExplosion::GetDamage()
{
	return Damage;
}

void AAExplosion::DealDamage(AAAPawn * TakingDamagePawn)
{
	if (TakingDamagePawn)
	{
		FDamageEvent DamageEvent;
		TakingDamagePawn->TakeDamage(GetDamage(), DamageEvent, GetInstigatorController(), GetInstigator());
	}
}

// Called when the game starts or when spawned
void AAExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//float ActualRadius = InitialRadius + (((InitialLifeSpan - GetLifeSpan()) / InitialLifeSpan) * (MaximalRadius - InitialRadius));
	//SquareCollisionComponent->SetSphereRadius(ActualRadius);
}

