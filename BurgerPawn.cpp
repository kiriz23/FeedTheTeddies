// Copyright A.T. Chamillard. All Rights Reserved.

#include "BurgerPawn.h"

#include "ScreenConstants.h"
#include "Kismet/GameplayStatics.h"
#include "EventManagerActor.h"

/**
 * Sets default values
*/
ABurgerPawn::ABurgerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

/**
 * Called when the game starts or when spawned
*/
void ABurgerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	// save bounds for pawn
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	HalfCollisionWidth = BoxExtent.Y;
	HalfCollisionHeight = BoxExtent.Z;

	// find static mesh component
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	// make sure we found the static mesh
	if (StaticMeshComponents.Num() > 0)
	{
		// the mesh we want is at location 0 because there's only 1 mesh
		UStaticMeshComponent* StaticMeshComponent = StaticMeshComponents[0];

		// set up delegate for collisions with something else
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(
			this, &ABurgerPawn::OnOverlapBegin);
	}

	// add to event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->AddGameOverEventInvoker(this);
	}

	// save for efficiency
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "ConfigurationData", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		ConfigurationData = Cast<AConfigurationDataActor>(
			TaggedActors[0]);
	}
}

/**
 * Called every frame
 * @param DeltaTime Game time elapsed during last frame modified by the time dilation
*/
void ABurgerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// move pawn based on movement input
	FVector PendingMovementInput = ConsumeMovementInputVector();
	if (PendingMovementInput.Y != 0 ||
		PendingMovementInput.Z != 0)
	{
		float MoveAmountPerSecond = ConfigurationData->GetBurgerMoveAmountPerSecond();
		FVector NewLocation = GetActorLocation();
		NewLocation.Y += PendingMovementInput.Y *
			MoveAmountPerSecond * DeltaTime;
		NewLocation.Y = FMath::Clamp(NewLocation.Y,
			ScreenConstants::Left + HalfCollisionWidth,
			ScreenConstants::Right - HalfCollisionWidth);
		NewLocation.Z += PendingMovementInput.Z *
			MoveAmountPerSecond * DeltaTime;
		NewLocation.Z = FMath::Clamp(NewLocation.Z,
			ScreenConstants::Bottom + HalfCollisionHeight,
			ScreenConstants::Top - HalfCollisionHeight - TopClampKludgeAmount);
		SetActorLocation(NewLocation);
	}
}

/**
 * Called when the burger overlaps with something else
*/
void ABurgerPawn::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check for objects that affect burger health
	if (OtherActor != nullptr)
	{
		// lose health for collisions with teddy bears and
		// teddy bear projectiles
		if (OtherActor->ActorHasTag("TeddyBear"))
		{
			// lose health and destroy teddy bear
			Health -= ConfigurationData->GetBearDamage();
			HealthPercent = StaticCast<float>(Health) / MaxHealth;
			UGameplayStatics::PlaySound2D(this,
				BurgerDamageCue);
			CheckGameOver();
		}
		else if (OtherActor->ActorHasTag("TeddyBearProjectile"))
		{
			// lose health and destroy teddy bear projectile
			Health -= ConfigurationData->GetBearProjectileDamage();
			HealthPercent = StaticCast<float>(Health) / MaxHealth;
			OtherActor->Destroy();
			UGameplayStatics::PlaySound2D(this,
				BurgerDamageCue);
			CheckGameOver();
		}
	}
}

/**
 * Moves burger horizontally
 * @param moveScale scale factor for movement
*/
void ABurgerPawn::MoveHorizontally(float moveScale)
{
	moveScale = FMath::Clamp(moveScale, -1.0f, 1.0f);
	AddMovementInput(GetActorRightVector(),
		moveScale);
}

/**
 * Moves burger vertically
 * @param moveScale scale factor for movement
*/
void ABurgerPawn::MoveVertically(float moveScale)
{
	moveScale = FMath::Clamp(moveScale, -1.0f, 1.0f);
	AddMovementInput(GetActorUpVector(),
		moveScale);
}

/**
 * Shoots french fries
*/
void ABurgerPawn::Shoot()
{
	// spawn fries
	FVector SpawnLocation{ GetActorLocation() };
	SpawnLocation.Z += HalfCollisionHeight;
	GetWorld()->SpawnActor<AFriesActor>(
		UFries, SpawnLocation,
		FRotator::ZeroRotator);

	UGameplayStatics::PlaySound2D(this,
		BurgerShotCue);
}

/**
 * Called when actor is being removed from level
 * @param EndPlayReason why the actor is being removed
*/
void ABurgerPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// remove from event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->RemoveGameOverEventInvoker(this);
	}
}

/**
 * Gets the points added event
*/
FGameOverEvent& ABurgerPawn::GetGameOverEvent()
{
	return GameOverEvent;
}

/**
 * Checks if the game is over because we're out of health
*/
void ABurgerPawn::CheckGameOver()
{
	if (Health <= 0)
	{
		UGameplayStatics::PlaySound2D(this,
			BurgerDeathCue);
		GameOverEvent.Broadcast();
	}
}