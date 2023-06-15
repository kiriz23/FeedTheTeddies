// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "DelegateDeclarations.h"
#include "ConfigurationDataActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FriesActor.generated.h"

/**
 * French fries (projectile)
*/
UCLASS()
class FEEDTHETEDDIES_API AFriesActor : public AActor
{
	GENERATED_BODY()
	
private:
	float HalfCollisionHeight;

	// points added event support
	FPointsAddedEvent PointsAddedEvent;

	// saved for efficiency
	AConfigurationDataActor* ConfigurationData;

public:	
	/**
	 * Sets default values for this actor's properties
	*/
	AFriesActor();

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
	 * Called when the fries overlaps with something else
	*/
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * Called when actor is being removed from level
	 * @param EndPlayReason why the actor is being removed
	*/
	UFUNCTION()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	 * Gets the points added event
	*/
	FPointsAddedEvent& GetPointsAddedEvent();
};
