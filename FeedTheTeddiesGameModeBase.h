// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "DelegateDeclarations.h"
#include "Blueprint/UserWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FeedTheTeddiesGameModeBase.generated.h"

/**
 * Custom game mode
 */
UCLASS()
class FEEDTHETEDDIES_API AFeedTheTeddiesGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HUD")
		TSubclassOf<UUserWidget> HudWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Over")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category = "Score")
		int Score{ 0 };
	UPROPERTY(BlueprintReadWrite, Category = "Seconds Left")
		int SecondsLeft{ 0 };

	/**
	 * Sets default values for this game mode's properties
	*/
	AFeedTheTeddiesGameModeBase();

protected:
	/**
	 * Called when the game starts or when spawned
	*/
	virtual void BeginPlay() override;

public:
	/**
	 * Adds points to the score
	 * @param Points points to add to score
	*/
	void AddPoints(int Points);

	/**
	 * Adds this object to the given points added event
	 * @param PointsAddedEvent points added event
	 * @return delegate handle
	*/
	FDelegateHandle AddToPointsAddedEvent(FPointsAddedEvent& PointsAddedEvent);

	/**
	 * Ends the game
	*/
	void EndGame();

	/**
	 * Adds this object to the given game over event
	 * @param GameOverEvent game over event
	 * @return delegate handle
	*/
	FDelegateHandle AddToGameOverEvent(FGameOverEvent& GameOverEvent);

	/**
	 * Called when actor is being removed from level
	 * @param EndPlayReason why the actor is being removed
	*/
	UFUNCTION()
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	 * Starts a one second timer
	*/
	void StartOneSecondTimer();

private:
	/**
	 * Changes displayed second left
	 * @param NewSecondsLeft new seconds left
	*/
	void ChangeSecondsLeft();
};
