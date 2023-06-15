// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "HomingActorInterface.h"
#include "HomingActorComponent.h"
#include "ConfigurationDataActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeddyBearProjectileActor.generated.h"

/**
 * A teddy bear projectile
*/
UCLASS()
class FEEDTHETEDDIES_API ATeddyBearProjectileActor : 
	public AActor, public IHomingActorInterface
{
	GENERATED_BODY()
	
private:
	float HalfCollisionHeight;

	// saved for efficiency
	AConfigurationDataActor* ConfigurationData;

	// saved for interface implementation
	UStaticMeshComponent* StaticMeshComponent;
	float ImpulseForce;

	// homing support
	UHomingActorComponent* HomingActorComponent;

public:	
	/**
	 * Sets default values for this actor's properties
	*/
	ATeddyBearProjectileActor();

protected:
	/**
	 * Called when the game starts or when spawned
	*/
	virtual void BeginPlay() override;

public:	
	/**
	 * Called every frame
	 * @param DeltaTime Game time elapsed during last frame modified by the time dilation 
	*/
	virtual void Tick(float DeltaTime) override;

	/**
	 * Gets a pointer to the static mesh for the actor
	 * @return static mesh
	*/
	virtual UStaticMeshComponent* GetStaticMesh() override;

	/**
	 * Gets the impulse force to use to move the actor
	 * @return impulse force
	*/
	virtual float GetImpulseForce() override;

	/**
	 * Gets the homing delay for the actor
	 * @return homing delay
	*/
	virtual float GetHomingDelay() override;
};
