// Fill out your copyright notice in the Description page of Project Settings.

#include "AAProjectile.h"
#include "AAPawn.h"

// Sets default values
AAAProjectile::AAAProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Static reference to the mesh to use for the projectile
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("/Game/TwinStick/Meshes/TwinStickProjectile.TwinStickProjectile"));

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	//ProjectileMesh->OnComponentBeginOverlap.AddDynamic(this, &AAAProjectile::BeginOverlap);	
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AAAProjectile::OnHit);	
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

													  // Die after 3 seconds by default
	InitialLifeSpan = 0.5f;
	bDestroyOnOverlap = true;
	UseDelay = 1.f;
	Damage = 1.f;
}

// Called when the game starts or when spawned
void AAAProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAAProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAAProjectile::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	//{
	//	
	//}
	Destroy();
}

void AAAProjectile::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (bDestroyOnOverlap)
	{
		Destroy();
	}
}

float AAAProjectile::GetDamage()
{
	float AdditionalDamage = 0;
	AAAPawn * Pawn = Cast<AAAPawn>(GetOwner());
	if (Pawn)
	{
		AdditionalDamage = Pawn->GetDamage();
	}
	return Damage;
}

float AAAProjectile::GetDelay()
{
	return UseDelay;
}

AAAPawn * AAAProjectile::GetProjectileOwner()
{
	return ProjectileOwner;
}

void AAAProjectile::SetProjectileOwner(AAAPawn * NProjectileOwner)
{
	ProjectileOwner = NProjectileOwner;
}
