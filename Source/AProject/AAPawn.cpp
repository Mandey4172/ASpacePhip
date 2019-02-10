// Fill out your copyright notice in the Description page of Project Settings.

#include "AAPawn.h"
#include "Skills/AThrowSkill.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AAAPawn::AAAPawn()
{
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComponent"));
	BoxCollisionComponent->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	BoxCollisionComponent->OnComponentHit.AddDynamic(this, &AAAPawn::OnHit);
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAAPawn::BeginOverlap);
	RootComponent = BoxCollisionComponent;
	
	ActorSpriteComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComponent"));
	ActorSpriteComponent->AttachTo(GetRootComponent());
	
	BaseSkillClass = AAThrowSkill::StaticClass();

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//
	bCanFire = true;
	//
	MaxHealth = 5.f;
	//
	Health = MaxHealth;
	// Movement
	MoveSpeed = 1000.0f;
	//
	SkillRate = 1.f;
	//
	Damage = 1.f;
}

// Called when the game starts or when spawned
void AAAPawn::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* const World = GetWorld();
	if (BaseSkillClass && World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = this;
		// Spawn 
		BaseSkill = World->SpawnActor<AASkill>(BaseSkillClass, SpawnParams);
	}
}

// Called every frame
void AAAPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AAAPawn::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Health -= DamageAmount;
	if (Health <= 0.0f)
	{
		Destroy();
		return 0.0f;
	}
	return DamageAmount;
}

void AAAPawn::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
}

void AAAPawn::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
}

void AAAPawn::UseBaseSkill()
{
	if (BaseSkill)
	{
		BaseSkill->Use(this);
	}
}

void AAAPawn::FireTimerExpired()
{
	bCanFire = true;
}

float AAAPawn::GetDamage()
{
	return Damage;
}

float AAAPawn::GetSkillRate()
{
	return SkillRate;
}

float AAAPawn::GetHealth()
{
	return Health;
}

FVector AAAPawn::GetFireDirection()
{
	return FVector::ZeroVector;
}



