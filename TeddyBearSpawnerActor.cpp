// Copyright A.T. Chamillard. All Rights Reserved.

#include "TeddyBearSpawnerActor.h"

#include "Kismet/GameplayStatics.h"

/**
 * Sets default values
*/
ATeddyBearSpawnerActor::ATeddyBearSpawnerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

/**
 * Called when the game starts or when spawned
*/
void ATeddyBearSpawnerActor::BeginPlay()
{
	Super::BeginPlay();

	// save for efficiency
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "ConfigurationData", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		ConfigurationData = Cast<AConfigurationDataActor>(
			TaggedActors[0]);
	}

	StartSpawnTimer();
}

/**
 * Called every frame
 * @param DeltaTime Game time elapsed during last frame modified by the time dilation
*/
void ATeddyBearSpawnerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * Spawns a teddy bear
*/
void ATeddyBearSpawnerActor::SpawnTeddyBear()
{
	// don't spawn more than max teddy bears
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "TeddyBear", TaggedActors);
	if (TaggedActors.Num() < ConfigurationData->GetMaxNumBears())
	{
		// generate random spawn location
		FVector SpawnLocation{ 0 };
		SpawnLocation.Y = FMath::RandRange(MinSpawnY, MaxSpawnY);
		SpawnLocation.Z = FMath::RandRange(MinSpawnZ, MaxSpawnZ);

		// spawn the teddy bear
		GetWorld()->SpawnActor<ATeddyBearActor>(
			UTeddyBear, SpawnLocation,
			FRotator::ZeroRotator);
	}

	// start the timer again
	StartSpawnTimer();
}

/**
 * Starts the spawn timer
*/
void ATeddyBearSpawnerActor::StartSpawnTimer()
{
	// set random duration and start the timer
	float TimerDuration = FMath::RandRange(
		ConfigurationData->GetMinSpawnDelay(), 
		ConfigurationData->GetMaxSpawnDelay());
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this,
		&ATeddyBearSpawnerActor::SpawnTeddyBear,
		TimerDuration);
}
