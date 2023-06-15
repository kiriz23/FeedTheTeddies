// Copyright A.T. Chamillard. All Rights Reserved.

#include "HomingActorComponent.h"

#include "HomingActorInterface.h"
#include "Kismet/GameplayStatics.h"

/**
 * Sets default values for this component's properties
*/
UHomingActorComponent::UHomingActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

/**
 * Called when the game starts
*/
void UHomingActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// save for efficiency
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "Burger", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		Target = Cast<ABurgerPawn>(TaggedActors[0]);
	}

	// save owner info for efficiency
	IHomingActorInterface* Owner = Cast<IHomingActorInterface>(GetOwner());
	StaticMeshComponent = Owner->GetStaticMesh();
	ImpulseForce = Owner->GetImpulseForce();
	HomingDelay = Owner->GetHomingDelay();

	StartHomingTimer();
}

/**
 * Called every frame
 * @param DeltaTime The time since the last tick
 * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
 * @param ThisTickFunction Internal tick function struct that caused this to run
*/
void UHomingActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

/**
 * Starts the homing timer
*/
void UHomingActorComponent::StartHomingTimer()
{
	FTimerHandle Timer;
	GetWorld()->GetTimerManager().SetTimer(Timer, this,
		&UHomingActorComponent::MoveTowardTarget,
		HomingDelay);
}

/**
 * Moves toward the target
*/
void UHomingActorComponent::MoveTowardTarget()
{
	StaticMeshComponent->SetAllPhysicsLinearVelocity(
		FVector::ZeroVector);
	FVector ForceVector = GetForceVector(
		GetOwner()->GetActorLocation(),
		Target->GetActorLocation());
	StaticMeshComponent->AddImpulse(ForceVector);

	StartHomingTimer();
}

/**
 * Gets the force vector to apply to the actor to go to target
 * @param ActorLocation actor location
 * @param TargetLocation target location
 * @return force vector
*/
FVector UHomingActorComponent::GetForceVector(FVector ActorLocation,
	FVector TargetLocation)
{
	FVector Direction = TargetLocation - ActorLocation;
	Direction.Normalize();
	return Direction * ImpulseForce;
}