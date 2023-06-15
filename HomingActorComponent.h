// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "BurgerPawn.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HomingActorComponent.generated.h"

/**
 * Gives the actor the component is attached to homing behavior
 * toward the burger
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FEEDTHETEDDIES_API UHomingActorComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	ABurgerPawn* Target;

	// save owner info for efficiency
	UStaticMeshComponent* StaticMeshComponent;
	float ImpulseForce{ 0 };
	float HomingDelay{ 0 };

	/**
	 * Starts the spawn timer
	*/
	void StartHomingTimer();

public:	
	/**
	 * Sets default values for this actor's properties
	*/
	UHomingActorComponent();

protected:
	/**
	 * Called when the game starts
	*/
	virtual void BeginPlay() override;

public:	
    /**
     * Called every frame
     * @param DeltaTime The time since the last tick
     * @param TickType The kind of tick this is, for example, are we paused, or 'simulating' in the editor
     * @param ThisTickFunction Internal tick function struct that caused this to run
    */
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Sets impulse force to the given force
	 * @param Force force
	*/
	void SetImpulseForce(float Force);

	/**
	 * Moves toward the target
	*/
	void MoveTowardTarget();

private:
	/**
	 * Gets the force vector to apply to the actor to go to target
	 * @param ActorLocation actor location
	 * @param TargetLocation target location
	 * @return force vector
	*/
	FVector GetForceVector(FVector ActorLocation,
		FVector TargetLocation);
};
