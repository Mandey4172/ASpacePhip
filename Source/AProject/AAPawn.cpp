// Fill out your copyright notice in the Description page of Project Settings.

#include "AAPawn.h"

#include "AThrowSkill.h"



// Sets default values
AAAPawn::AAAPawn()
{
	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereComponent"));
	BoxCollisionComponent->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	BoxCollisionComponent->OnComponentHit.AddDynamic(this, &AAAPawn::OnHit);
	//BoxCollisionComponent->BodyInstance.SetCollisionProfileName();
	RootComponent = BoxCollisionComponent;

	ActorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ActorMeshComponent->AttachTo(GetRootComponent());
	//ActorMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AAAPawn::BeginOverlap);
	
	BaseSkillClass = AAThrowSkill::StaticClass();

 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//
	bCanFire = true;
	//
	Health = 5.f;
	// Movement
	MoveSpeed = 1000.0f;
	//
	SkillRate = 1.f;
	//
	Damage = 1.f;

	FireDirection = FVector::ZeroVector;
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
		// spawn 
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
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Take damage!"));
	Health -= DamageAmount;
	if (Health <= 0.0f)
	{
		Destroy();
	}
	return 0.0f;
}

void AAAPawn::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overleap!"));
}

void AAAPawn::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	int x = 0;
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

FVector AAAPawn::GetFireDirection()
{
	return FireDirection;
}



