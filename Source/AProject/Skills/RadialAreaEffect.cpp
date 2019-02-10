// Fill out your copyright notice in the Description page of Project Settings.

#include "RadialAreaEffect.h"
#include "PaperFlipbookComponent.h"
#include "AAPawn.h"

// Sets default values
ARadialAreaEffect::ARadialAreaEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SquareCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	SquareCollisionComponent->SetSphereRadius(10.f);
	SquareCollisionComponent->SetupAttachment(RootComponent);
	SquareCollisionComponent->BodyInstance.SetCollisionProfileName("OverllapAll");
	SquareCollisionComponent->OnComponentHit.AddDynamic(this, &ARadialAreaEffect::OnHit);
	SquareCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARadialAreaEffect::BeginOverlap);
	SquareCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ARadialAreaEffect::EndOverlap);
	RootComponent = SquareCollisionComponent;

	// Create flipbook component for the projectile sphere
	EffectSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("SpriteComponent"));
	EffectSprite->AttachTo(GetRootComponent());

	DamagePerTick = 1.f;
	TickTime = 1.f;
	//ElapsedTime = 0.f
}

void ARadialAreaEffect::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAAPawn * Pawn = Cast<AAAPawn>(OtherActor);
	DealDamage(Pawn);
	TickHandler Handler;
	Handler.Pawn = Pawn;
	Handler.ElapsedTime = 0.f;
	TickHandlers.Add(Handler);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AreaEffect BeginOverleap"));
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overleap!"));
}

void ARadialAreaEffect::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AAAPawn * Pawn = Cast<AAAPawn>(OtherActor);
	TickHandler Handler;
	Handler.Pawn = Pawn;
	TickHandlers.Remove(Handler);
}

void ARadialAreaEffect::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OnHit!"));
}

float ARadialAreaEffect::GetDamage()
{
	return DamagePerTick;
}

void ARadialAreaEffect::DealDamage(AAAPawn * TakingDamagePawn)
{
	if (TakingDamagePawn)
	{
		FDamageEvent DamageEvent;
		TakingDamagePawn->TakeDamage(GetDamage(), DamageEvent, GetInstigatorController(), GetInstigator());
	}
}

// Called when the game starts or when spawned
void ARadialAreaEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARadialAreaEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (TickHandler& Handler : TickHandlers)
	{
		Handler.ElapsedTime += DeltaTime;
		if (Handler.ElapsedTime > TickTime)
		{
			Handler.ElapsedTime -= TickTime;
			DealDamage(Handler.Pawn);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AreaEffect Tick"));
		}
	}
}

