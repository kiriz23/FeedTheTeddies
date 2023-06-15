// Copyright A.T. Chamillard. All Rights Reserved.


#include "TeddyBearActor.h"

#include "ScreenConstants.h"
#include "Kismet/GameplayStatics.h"
#include "ConfigurationDataActor.h"

/**
 * Sets default values
*/
ATeddyBearActor::ATeddyBearActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

/**
 * Called when the game starts or when spawned
*/
void ATeddyBearActor::BeginPlay()
{
	Super::BeginPlay();

	// save bounds for actor
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	HalfCollisionWidth = BoxExtent.Y;
	HalfCollisionHeight = BoxExtent.Z;

	// find configuration data
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "ConfigurationData", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		ConfigurationData = Cast<AConfigurationDataActor>(
			TaggedActors[0]);
	}

	// find static mesh component
	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents(StaticMeshComponents);

	// make sure we found the static mesh
	if (StaticMeshComponents.Num() > 0)
	{
		// the mesh we want is at location 0 because there's only 1 mesh
		StaticMeshComponent = StaticMeshComponents[0];

		// set up delegate for collisions with something else
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(
			this, &ATeddyBearActor::OnOverlapBegin);

		// add random force
		ImpulseForce = FMath::RandRange(
			ConfigurationData->GetMinBearImpulseForce(),
			ConfigurationData->GetMaxBearImpulseForce());
		FVector Force{ 0 };
		float Angle = FMath::RandRange(0.0f, 2 * 3.14159f);
		Force.Y = FMath::Cos(Angle) * ImpulseForce;
		Force.Z = FMath::Sin(Angle) * ImpulseForce;
		StaticMeshComponent->AddImpulse(Force);
	}

	StartShootTimer();

	// add, check, and register homing component
	HomingActorComponent = NewObject<UHomingActorComponent>(this);
	check(HomingActorComponent != nullptr);
	HomingActorComponent->RegisterComponent();
}

/**
 * Called every frame
 * @param DeltaTime Game time elapsed during last frame modified by the time dilation
*/
void ATeddyBearActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// wrap if off screen
	if (IsOffScreen())
	{
		FVector Location = GetActorLocation();

		// wrap horizontally
		if (Location.Y < ScreenConstants::Left - HalfCollisionWidth ||
			Location.Y > ScreenConstants::Right + HalfCollisionWidth)
		{
			Location.Y *= -1;
		}

		// wrap vertically
		if (Location.Z > ScreenConstants::Top + HalfCollisionHeight ||
			Location.Z < ScreenConstants::Bottom - HalfCollisionHeight)
		{
			Location.Z *= -1;
		}

		SetActorLocation(Location);
	}
}

/**
 * Called when the teddy bear overlaps with something else
*/
void ATeddyBearActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		// check for objects that kill teddy bear
		if (OtherActor->ActorHasTag("Burger") ||
			OtherActor->ActorHasTag("Fries"))
		{
			UGameplayStatics::PlaySound2D(this,
				TeddyDeathCue);
			Destroy();
		}
		else if (OtherActor->ActorHasTag("TeddyBearProjectile"))
		{	
			// destroy teddy bear projectiles
			OtherActor->Destroy();
		}
	}
}


/**
 * Tells whether or not the teddy bear is off the screen
 * @return true if the teddy bear is off screen, false otherwise
*/
bool ATeddyBearActor::IsOffScreen()
{
	FVector Location = GetActorLocation();
	return Location.Y < ScreenConstants::Left - HalfCollisionWidth ||
		Location.Y > ScreenConstants::Right + HalfCollisionWidth ||
		Location.Z > ScreenConstants::Top + HalfCollisionHeight ||
		Location.Z < ScreenConstants::Bottom - HalfCollisionHeight;
}

/**
 * Shoots a projectile
*/
void ATeddyBearActor::ShootProjectile()
{
	// spawn projectile
	FVector SpawnLocation{ GetActorLocation() };
	SpawnLocation.Z -= HalfCollisionHeight + 
		ProjectileOffsetAmount;
	GetWorld()->SpawnActor<ATeddyBearProjectileActor>(
		UProjectile, SpawnLocation,
		FRotator::ZeroRotator);

	UGameplayStatics::PlaySound2D(this,
		TeddyShotCue);

	// start the timer again
	StartShootTimer();
}

/**
 * Starts the shoot timer
*/
void ATeddyBearActor::StartShootTimer()
{
	// set random duration and start the timer
	float TimerDuration = FMath::RandRange(
		ConfigurationData->GetBearMinShotDelay(),
		ConfigurationData->GetBearMaxShotDelay());
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this,
		&ATeddyBearActor::ShootProjectile,
		TimerDuration);
}

/**
 * Gets a pointer to the static mesh for the actor
 * @return static mesh
*/
UStaticMeshComponent* ATeddyBearActor::GetStaticMesh()
{
	return StaticMeshComponent;
}

/**
 * Gets the impulse force to use to move the actor
 * @return impulse force
*/
float ATeddyBearActor::GetImpulseForce()
{
	return ImpulseForce;
}

/**
 * Gets the homing delay for the actor
 * @return homing delay
*/
float ATeddyBearActor::GetHomingDelay()
{
	return ConfigurationData->GetBearHomingDelay();
}