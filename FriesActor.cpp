// Copyright A.T. Chamillard. All Rights Reserved.

#include "FriesActor.h"

#include "ScreenConstants.h"
#include "Kismet/GameplayStatics.h"
#include "EventManagerActor.h"

/**
 * Sets default values
*/
AFriesActor::AFriesActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

/**
 * Called when the game starts or when spawned
*/
void AFriesActor::BeginPlay()
{
	Super::BeginPlay();

	// save half collision height
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	HalfCollisionHeight = BoxExtent.Z;

	// add to event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->AddPointsAddedEventInvoker(this);
	}

	// save for efficiency
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
		UStaticMeshComponent* StaticMeshComponent = StaticMeshComponents[0];

		// set up delegate for collisions with something else
		StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(
			this, &AFriesActor::OnOverlapBegin);

		// get fries moving
		FVector Force{ 0.0f, 0.0f,
			ConfigurationData->GetFriesImpulseForce() };
		StaticMeshComponent->AddImpulse(Force);
	}
}

/**
 * Called every frame
 * @param DeltaTime Game time elapsed during last frame modified by the time dilation
*/
void AFriesActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// destroy if past top of screen
	if (GetActorLocation().Z >
		ScreenConstants::Top + HalfCollisionHeight)
	{
		Destroy();
	}
}

/**
 * Called when the fries overlaps with something else
*/
void AFriesActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check for objects that destroy fries
	if (OtherActor != nullptr)
	{
		// earn points for collisions with teddy bears
		if (OtherActor->ActorHasTag("TeddyBear"))
		{
			// add points and destroy fries
			PointsAddedEvent.Broadcast(ConfigurationData->GetBearPoints());
			Destroy();
		}
		else if (OtherActor->ActorHasTag("Fries") ||
			OtherActor->ActorHasTag("TeddyBearProjectile"))
		{
			OtherActor->Destroy();
			Destroy();
		}
	}
}

/**
 * Called when actor is being removed from level
 * @param EndPlayReason why the actor is being removed
*/
void AFriesActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// remove from event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->RemovePointsAddedEventInvoker(this);
	}
}

/**
 * Gets the points added event
*/
FPointsAddedEvent& AFriesActor::GetPointsAddedEvent()
{
	return PointsAddedEvent;
}

