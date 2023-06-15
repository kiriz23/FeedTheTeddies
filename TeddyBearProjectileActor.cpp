// Copyright A.T. Chamillard. All Rights Reserved.

#include "TeddyBearProjectileActor.h"

#include "ScreenConstants.h"
#include "Kismet/GameplayStatics.h"

/**
 * Sets default values
*/
ATeddyBearProjectileActor::ATeddyBearProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

/**
 * Called when the game starts or when spawned
*/
void ATeddyBearProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	// save half collision height
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	HalfCollisionHeight = BoxExtent.Z;

	// save for efficiency
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

		// get projectile moving
		ImpulseForce = ConfigurationData->GetBearProjectileImpulseForce();
		FVector Force{ 0.0f, 0.0f, -ImpulseForce };
		StaticMeshComponent->AddImpulse(Force);
	}

	// add, check, and register homing component
	HomingActorComponent = NewObject<UHomingActorComponent>(this);
	check(HomingActorComponent != nullptr);
	HomingActorComponent->RegisterComponent();
}


/**
 * Called every frame
 * @param DeltaTime Game time elapsed during last frame modified by the time dilation
*/
void ATeddyBearProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// destroy if past bottom of screen
	if (GetActorLocation().Z <
		ScreenConstants::Bottom - HalfCollisionHeight)
	{
		Destroy();
	}
}

/**
 * Gets a pointer to the static mesh for the actor
 * @return static mesh
*/
UStaticMeshComponent* ATeddyBearProjectileActor::GetStaticMesh()
{
	return StaticMeshComponent;
}

/**
 * Gets the impulse force to use to move the actor
 * @return impulse force
*/
float ATeddyBearProjectileActor::GetImpulseForce()
{
	return ImpulseForce;
}

/**
 * Gets the homing delay for the actor
 * @return homing delay
*/
float ATeddyBearProjectileActor::GetHomingDelay()
{
	return ConfigurationData->GetBearProjectileHomingDelay();
}