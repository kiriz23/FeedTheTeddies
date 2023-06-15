// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "HomingActorInterface.h"
#include "HomingActorComponent.h"
#include "TeddyBearProjectileActor.h"
#include "Sound/SoundCue.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeddyBearActor.generated.h"

/**
 * A teddy bear
*/
UCLASS()
class FEEDTHETEDDIES_API ATeddyBearActor : 
	public AActor, public IHomingActorInterface
{
	GENERATED_BODY()
	
private:
	float HalfCollisionWidth;
	float HalfCollisionHeight;
	float ProjectileOffsetAmount{ 2 };

	// saved for efficiency
	AConfigurationDataActor* ConfigurationData;

	// saved for interface implementation
	UStaticMeshComponent* StaticMeshComponent;
	float ImpulseForce;

	// homing support
	UHomingActorComponent* HomingActorComponent;

	/**
	 * Starts the spawn timer
	*/
	void StartShootTimer();

public:	
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "Projectile"),
		Category = ProjectileBlueprints)
		TSubclassOf<ATeddyBearProjectileActor> UProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* TeddyShotCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* TeddyDeathCue;

	/**
	 * Shoots a projectile
	*/
	UFUNCTION()
		void ShootProjectile();

	/**
	 * Sets default values for this actor's properties
	*/
	ATeddyBearActor();

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
	 * Called when the teddy bear overlaps with something else
	*/
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

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

private:
	/**
	 * Tells whether or not the teddy bear is off the screen
	 * @return true if the teddy bear is off screen, false otherwise
	*/
	bool IsOffScreen();
};
