// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HomingActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHomingActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * An interface for actors with homing behavior
 */
class FEEDTHETEDDIES_API IHomingActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/**
	 * Gets a pointer to the static mesh for the actor
	 * @return static mesh
	*/
	virtual UStaticMeshComponent* GetStaticMesh() PURE_VIRTUAL(IHomingActorInterface::GetStaticMesh, return nullptr;);

	/**
	 * Gets the impulse force to use to move the actor
	 * @return impulse force
	*/
	virtual float GetImpulseForce() PURE_VIRTUAL(IHomingActorInterface::GetImpulseForce, return 0;);

	/**
	 * Gets the homing delay for the actor
	 * @return homing delay
	*/
	virtual float GetHomingDelay() PURE_VIRTUAL(IHomingActorInterface::GetHomingDelay, return 0;);

};
