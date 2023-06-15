// Copyright A.T. Chamillard. All Rights Reserved.

#include "ConfigurationDataActor.h"

#include "Kismet/GameplayStatics.h"
#include "FeedTheTeddiesSaveGame.h"

// Sets default values
AConfigurationDataActor::AConfigurationDataActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConfigurationDataActor::BeginPlay()
{
	Super::BeginPlay();
	
	// open save game and save difficulty
	// note: the main menu actor makes sure a save game exists
	UFeedTheTeddiesSaveGame* SaveGameInstance = Cast<UFeedTheTeddiesSaveGame>(
		UGameplayStatics::LoadGameFromSlot(
			"FeedTheTeddiesSaveSlot", 0));
	Difficulty = SaveGameInstance->Difficulty;

	// retrieve configuration data from data table
	FString ContextString;
	ConfigurationDataRow =
		ConfigurationDataTable->FindRow<FConfigurationDataStruct>(
			"ConfigData", ContextString);
}

// Called every frame
void AConfigurationDataActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * Gets the total game seconds
 * @return total game seconds
*/
int AConfigurationDataActor::GetTotalGameSeconds()
{
	return ConfigurationDataRow->TotalGameSeconds;
}

/**
 * Gets the burger move amount per second
 * @return burger move amount per second
*/
float AConfigurationDataActor::GetBurgerMoveAmountPerSecond()
{
	return ConfigurationDataRow->BurgerMoveAmountPerSecond;
}

/**
 * Gets the bear damage
 * @return bear damage
*/
int AConfigurationDataActor::GetBearDamage()
{
	return ConfigurationDataRow->BearDamage;
}

/**
 * Gets the bear projectile damage
 * @return bear projectile damage
*/
int AConfigurationDataActor::GetBearProjectileDamage()
{
	return ConfigurationDataRow->BearProjectileDamage;

}

/**
 * Gets the bear points
 * @return bear points
*/
int AConfigurationDataActor::GetBearPoints()
{
	return ConfigurationDataRow->BearPoints;
}

/**
 * Gets the fries impulse force
 * @return fries impulse force
*/
float AConfigurationDataActor::GetFriesImpulseForce()
{
	return ConfigurationDataRow->FriesImpulseForce;
}

/**
 * Gets the bear projectile impulse force
 * @return bear projectile impulse force
*/
float AConfigurationDataActor::GetBearProjectileImpulseForce()
{
	return ConfigurationDataRow->BearProjectileImpulseForce;
}

/**
 * Gets the min spawn delay
 * @return min spawn delay
*/
float AConfigurationDataActor::GetMinSpawnDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMinSpawnDelay;
	case 1: return ConfigurationDataRow->MediumMinSpawnDelay;
	case 2: return ConfigurationDataRow->HardMinSpawnDelay;
	default: return ConfigurationDataRow->EasyMinSpawnDelay;
	}
}

/**
 * Gets the max spawn delay
 * @return max spawn delay
*/
float AConfigurationDataActor::GetMaxSpawnDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMaxSpawnDelay;
	case 1: return ConfigurationDataRow->MediumMaxSpawnDelay;
	case 2: return ConfigurationDataRow->HardMaxSpawnDelay;
	default: return ConfigurationDataRow->EasyMaxSpawnDelay;
	}
}

/**
 * Gets the min bear impulse force
 * @return min bear impulse force
*/
float AConfigurationDataActor::GetMinBearImpulseForce()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMinBearImpulseForce;
	case 1: return ConfigurationDataRow->MediumMinBearImpulseForce;
	case 2: return ConfigurationDataRow->HardMinBearImpulseForce;
	default: return ConfigurationDataRow->EasyMinBearImpulseForce;
	}
}

/**
 * Gets the max bear impulse force
 * @return max bear impulse force
*/
float AConfigurationDataActor::GetMaxBearImpulseForce()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMaxBearImpulseForce;
	case 1: return ConfigurationDataRow->MediumMaxBearImpulseForce;
	case 2: return ConfigurationDataRow->HardMaxBearImpulseForce;
	default: return ConfigurationDataRow->EasyMaxBearImpulseForce;
	}
}

/**
 * Gets the max number of bears
 * @return max number of bears
*/
int AConfigurationDataActor::GetMaxNumBears()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyMaxNumBears;
	case 1: return ConfigurationDataRow->MediumMaxNumBears;
	case 2: return ConfigurationDataRow->HardMaxNumBears;
	default: return ConfigurationDataRow->EasyMaxNumBears;
	}
}

/**
 * Gets the bear min shot delay
 * @return bear min shot delay
*/
float AConfigurationDataActor::GetBearMinShotDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyBearMinShotDelay;
	case 1: return ConfigurationDataRow->MediumBearMinShotDelay;
	case 2: return ConfigurationDataRow->HardBearMinShotDelay;
	default: return ConfigurationDataRow->EasyBearMinShotDelay;
	}
}

/**
 * Gets the bear max shot delay
 * @return bear max shot delay
*/
float AConfigurationDataActor::GetBearMaxShotDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyBearMaxShotDelay;
	case 1: return ConfigurationDataRow->MediumBearMaxShotDelay;
	case 2: return ConfigurationDataRow->HardBearMaxShotDelay;
	default: return ConfigurationDataRow->EasyBearMaxShotDelay;
	}
}

/**
 * Gets the bear homing delay
 * @return bear homing delay
*/
float AConfigurationDataActor::GetBearHomingDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyBearHomingDelay;
	case 1: return ConfigurationDataRow->MediumBearHomingDelay;
	case 2: return ConfigurationDataRow->HardBearHomingDelay;
	default: return ConfigurationDataRow->EasyBearHomingDelay;
	}
}

/**
 * Gets the bear projectile homing delay
 * @return bear projectile homing delay
*/
float AConfigurationDataActor::GetBearProjectileHomingDelay()
{
	switch (Difficulty)
	{
	case 0: return ConfigurationDataRow->EasyBearProjectileHomingDelay;
	case 1: return ConfigurationDataRow->MediumBearProjectileHomingDelay;
	case 2: return ConfigurationDataRow->HardBearProjectileHomingDelay;
	default: return ConfigurationDataRow->EasyBearProjectileHomingDelay;
	}
}