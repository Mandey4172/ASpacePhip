// Fill out your copyright notice in the Description page of Project Settings.

#include "AMealeStrike.h"
#include "AAPlayerPawn.h"
#include "AAEnemyPawn.h"

// Sets default values
AAMealeStrike::AAMealeStrike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereCollisionComponent->InitSphereRadius(100.f);
	SphereCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAMealeStrike::BeginOverlapSphere);
	SphereCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AAMealeStrike::EndOverlapSphere);
	//SphereCollisionComponent->InitBoxExtent(FVector(50.f, 50.f, 50.f));
	
	//BoxCollisionComponent->BodyInstance.SetCollisionProfileName();
	RootComponent = SphereCollisionComponent;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxCollisionComponent->InitBoxExtent(FVector(50.f, 100.f, 100.f));
	BoxCollisionComponent->AddLocalOffset(FVector(50.f, 0.f, 0.f));
	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AAMealeStrike::BeginOverlapBox);
	BoxCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AAMealeStrike::EndOverlapBox);
	BoxCollisionComponent->AttachTo(GetRootComponent());
	//BoxCollisionComponent->BodyInstance.SetCollisionProfileName();
	
	InitialLifeSpan = 0.1f;
	bSphereOverleaping = false;
	bBoxOverlaping = false;
	bOverlaping = false;
}

void AAMealeStrike::SetSkillOwner(AAAPawn * NOwningPawn)
{
	OwningPawn = NOwningPawn;
}

// Called when the game starts or when spawned
void AAMealeStrike::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAMealeStrike::BeginOverlapSphere(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (BoxCollisionComponent->IsOverlappingActor(OtherActor))
	{
		bOverlaping = true;
		BeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,SweepResult);
	}
}

void AAMealeStrike::EndOverlapSphere(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (BoxCollisionComponent->IsOverlappingActor(OtherActor))
	{
		EndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	}
}

void AAMealeStrike::BeginOverlapBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (SphereCollisionComponent->IsOverlappingActor(OtherActor))
	{
		BeginOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

void AAMealeStrike::EndOverlapBox(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (SphereCollisionComponent->IsOverlappingActor(OtherActor))
	{
		EndOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	}
}

void AAMealeStrike::BeginOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if((OtherActor != this) && (GetInstigator() != OtherActor))
	{
		AAAPlayerPawn * Player = Cast<AAAPlayerPawn>(OtherActor);
		AAAEnemyPawn * Enemy = Cast<AAAEnemyPawn>(GetInstigator());
		if (Player && Enemy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Begin Overlap 1"));
		}
		Player = Cast<AAAPlayerPawn>(GetInstigator());
		Enemy = Cast<AAAEnemyPawn>(OtherActor);
		if (Player && Enemy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Begin Overlap 2"));
			return;
		}
	}
}

void AAMealeStrike::EndOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != this) && (OwningPawn != OtherActor))
	{
		AAAPlayerPawn * Player = Cast<AAAPlayerPawn>(OtherActor);
		AAAEnemyPawn * Enemy = Cast<AAAEnemyPawn>(OwningPawn);
		if (Player && Enemy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Overlap 1"));
			return;
		}
		Player = Cast<AAAPlayerPawn>(OwningPawn);
		Enemy = Cast<AAAEnemyPawn>(OtherActor);
		if (Player && Enemy)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End Overlap 2"));
			return;
		}
	}
}

// Called every frame
void AAMealeStrike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

