// Fill out your copyright notice in the Description page of Project Settings.

#include "AAPlayerPawn.h"
#include "AAProjectile.h"

const FName AAAPlayerPawn::MoveForwardBinding("MoveForward");
const FName AAAPlayerPawn::MoveRightBinding("MoveRight");
const FName AAAPlayerPawn::FireForwardBinding("FireForward");
const FName AAAPlayerPawn::FireRightBinding("FireRight");

AAAPlayerPawn::AAAPlayerPawn()
{
	
}

void AAAPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);

	// Calculate  movement
	const FVector Movement = MoveDirection * MoveSpeed * DeltaTime;

	// If non-zero size, move this actor
	if (Movement.SizeSquared() > 0.0f)
	{
		const FRotator NewRotation = GetActorRotation();
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
		SetActorRotation(Movement.Rotation());
		if (Hit.IsValidBlockingHit())
		{
			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, NewRotation, true);
		}
	}

	// Create fire direction vector
	const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
	const float FireRightValue = GetInputAxisValue(FireRightBinding);
	FireDirection = FVector(FireForwardValue, FireRightValue, 0.f).GetClampedToMaxSize(1.0f);
	if (FireDirection != FVector::ZeroVector)
	{
		SetActorRotation(FireDirection.Rotation());
		// Try and fire a shot
		UseBaseSkill();
	}
}

void AAAPlayerPawn::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AAAProjectile * Projectile = Cast<AAAProjectile>(OtherActor);
	if (Projectile)
	{
		if (Projectile->GetInstigator() != this)
		{
			FDamageEvent DamageEvent;
			TakeDamage(Projectile->GetDamage(), DamageEvent,nullptr, Projectile->GetOwner());
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overleap!"));
}

void AAAPlayerPawn::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	AAAProjectile * Projectile = Cast<AAAProjectile>(OtherActor);
	if (Projectile)
	{
		if (Projectile->GetInstigator() != this)
		{
			FDamageEvent DamageEvent;
			TakeDamage(Projectile->GetDamage(), DamageEvent, nullptr, Projectile->GetOwner());
		}
	}
}


void AAAPlayerPawn::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// set up gameplay key bindings
	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
	PlayerInputComponent->BindAxis(FireForwardBinding);
	PlayerInputComponent->BindAxis(FireRightBinding);
}
