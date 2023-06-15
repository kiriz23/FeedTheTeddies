// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "Sound/SoundCue.h"
#include "FriesActor.h"
#include "DelegateDeclarations.h"

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BurgerPawn.generated.h"

/**
 * A burger pawn
*/
UCLASS()
class FEEDTHETEDDIES_API ABurgerPawn : public APawn
{
	GENERATED_BODY()

private:
	float HalfCollisionWidth;
	float HalfCollisionHeight;
	float TopClampKludgeAmount{ 3.5f };

	// game over event support
	FGameOverEvent GameOverEvent;

	// saved for efficiency
	AConfigurationDataActor* ConfigurationData;

public:
	UPROPERTY(EditAnywhere,
		meta = (MetaClass = "Fries"),
		Category = FriesBlueprints)
		TSubclassOf<AFriesActor> UFries;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* BurgerDamageCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* BurgerDeathCue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
		Category = "Sound")
		USoundCue* BurgerShotCue;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
		float HealthPercent{ 1.0f };
	const int MaxHealth{ 100 };
	int Health{ 100 };

	/**
	 * Sets default values for this pawn's properties
	*/
	ABurgerPawn();

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
	 * Called when the burger overlaps with something else
	*/
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp,
			class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * Moves burger horizontally
	 * @param moveScale scale factor for movement
	*/
	void MoveHorizontally(float moveScale);

	/**
	 * Moves burger vertically
	 * @param moveScale scale factor for movement
	*/
	void MoveVertically(float moveScale);

	/**
	 * Shoots french fries
	*/
	void Shoot();

	/**
	 * Called when actor is being removed from level
	 * @param EndPlayReason why the actor is being removed
	*/
	UFUNCTION()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	 * Gets the game over event
	*/
	FGameOverEvent& GetGameOverEvent();

private:
	/**
	 * Checks if the game is over because we're out of health
	*/
	void CheckGameOver();
};
