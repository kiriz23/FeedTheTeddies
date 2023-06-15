// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "Engine/DataTable.h"
#include "ConfigurationDataStruct.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConfigurationDataActor.generated.h"

UCLASS()
class FEEDTHETEDDIES_API AConfigurationDataActor : public AActor
{
	GENERATED_BODY()
	
private:
	// saved for efficiency
	int Difficulty{ 0 };
	FConfigurationDataStruct* ConfigurationDataRow{ nullptr };

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Configuration Data Table")
		UDataTable* ConfigurationDataTable;

	/**
	 * Sets default values for this actor's properties
	*/
	AConfigurationDataActor();

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
	 * Gets the total game seconds
	 * @return total game seconds
	*/
	int GetTotalGameSeconds();

	/**
	 * Gets the burger move amount per second
	 * @return burger move amount per second
	*/
	float GetBurgerMoveAmountPerSecond();

	/**
	 * Gets the bear damage
	 * @return bear damage
	*/
	int GetBearDamage();

	/**
	 * Gets the bear projectile damage
	 * @return bear projectile damage
	*/
	int GetBearProjectileDamage();

	/**
	 * Gets the bear points
	 * @return bear points
	*/
	int GetBearPoints();

	/**
	 * Gets the fries impulse force
	 * @return fries impulse force
	*/
	float GetFriesImpulseForce();

	/**
	 * Gets the bear projectile impulse force
	 * @return bear projectile impulse force
	*/
	float GetBearProjectileImpulseForce();

	/**
	 * Gets the min spawn delay
	 * @return min spawn delay
	*/
	float GetMinSpawnDelay();

	/**
	 * Gets the max spawn delay
	 * @return max spawn delay
	*/
	float GetMaxSpawnDelay();

	/**
	 * Gets the min bear impulse force
	 * @return min bear impulse force
	*/
	float GetMinBearImpulseForce();

	/**
	 * Gets the max bear impulse force
	 * @return max bear impulse force
	*/
	float GetMaxBearImpulseForce();

	/**
	 * Gets the max number of bears
	 * @return max number of bears
	*/
	int GetMaxNumBears();

	/**
	 * Gets the bear min shot delay
	 * @return bear min shot delay
	*/
	float GetBearMinShotDelay();

	/**
	 * Gets the bear max shot delay
	 * @return bear max shot delay
	*/
	float GetBearMaxShotDelay();

	/**
	 * Gets the bear homing delay
	 * @return bear homing delay
	*/
	float GetBearHomingDelay();

	/**
	 * Gets the bear projectile homing delay
	 * @return bear projectile homing delay
	*/
	float GetBearProjectileHomingDelay();
};
