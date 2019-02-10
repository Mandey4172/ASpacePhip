// Fill out your copyright notice in the Description page of Project Settings.

#include "AProjectile.h"
#include "AAPawn.h"
#include "PaperFlipbookComponent.h"

// Sets default values
AAProjectile::AAProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//
	SquareCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SquareCollisionComponent->SetSphereRadius(10.f);
	SquareCollisionComponent->SetupAttachment(RootComponent);
	SquareCollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	SquareCollisionComponent->OnComponentHit.AddDynamic(this, &AAProjectile::OnHit);
	SquareCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAProjectile::BeginOverlap);
	SquareCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AAProjectile::EndOverlap);
	RootComponent = SquareCollisionComponent;

	// Create flipbook component for the projectile sphere
	ProjectileSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComponent"));
	ProjectileSprite->AttachTo(GetRootComponent());

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = RootComponent;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	Distance = 1500.f;
	bDestroyOnOverlap = true;
}

// Called when the game starts or when spawned
void AAProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(Distance / ProjectileMovement->InitialSpeed);
}

// Called every frame
void AAProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAProjectile::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bDestroyOnOverlap)
	{
		Destroy();
	}
}

void AAProjectile::EndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void AAProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Destroy();
}

AAAPawn * AAProjectile::GetProjectileOwner()
{
	return ProjectileOwner;
}

void AAProjectile::SetProjectileOwner(AAAPawn * NProjectileOwner)
{
	ProjectileOwner = NProjectileOwner;
}
