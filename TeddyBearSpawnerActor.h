// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "TeddyBearActor.h"
#include "ConfigurationDataActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeddyBearSpawnerActor.generated.h"

/**
 * A teddy bear spawner
*/
UCLASS()
class FEEDTHETEDDIES_API ATeddyBearSpawnerActor : public AActor
{
	GENERATED_BODY()
	
private:
	// spawn location support
	const float MinSpawnY{ -200 };
	const float MaxSpawnY{ 200 };
	const float MinSpawnZ{ 0 };
	const float MaxSpawnZ{ 100 };

	// saved for efficiency
	AConfigurationDataActor* ConfigurationData;

	/**
	 * Starts the spawn timer
	*/
	void StartSpawnTimer();

public:
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "TeddyBear"),
		Category = TeddyBearBlueprints)
		TSubclassOf<ATeddyBearActor> UTeddyBear;

	/**
	 * Spawns a teddy bear
	*/
	UFUNCTION()
		void SpawnTeddyBear();

	/**
	 * Sets default values for this actor's properties
	*/
	ATeddyBearSpawnerActor();

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

};
