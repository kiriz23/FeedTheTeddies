// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "BurgerPawn.h"
#include "FriesActor.h"
#include "FeedTheTeddiesGameModeBase.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventManagerActor.generated.h"

/**
 * An event manager
*/
UCLASS()
class FEEDTHETEDDIES_API AEventManagerActor : public AActor
{
	GENERATED_BODY()
	
private:
	// points added event support
	TArray<AFriesActor*> PointsAddedEventInvokers;
	TMap<AFeedTheTeddiesGameModeBase*, TMap<AFriesActor*, FDelegateHandle>> PointsAddedEventListeners;

	// game over event support
	TArray<ABurgerPawn*> GameOverEventInvokers;
	TMap<AFeedTheTeddiesGameModeBase*, TMap<ABurgerPawn*, FDelegateHandle>> GameOverEventListeners;

public:	
	/**
	 * Sets default values for this actor's properties
	*/
	AEventManagerActor();

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
	 * Adds the given invoker as an invoker of the points added event
	 * @param Invoker invoker
	*/
	void AddPointsAddedEventInvoker(AFriesActor* Invoker);

	/**
	 * Removes the given invoker as an invoker of the points added event
	 * @param Invoker invoker
	*/
	void RemovePointsAddedEventInvoker(AFriesActor* Invoker);

	/**
	 * Adds the given listener as a listener for the points added event
	 * @param Listener listener
	*/
	void AddPointsAddedEventListener(AFeedTheTeddiesGameModeBase* Listener);

	/**
	 * Removes the given listener as a listener for the points added event
	 * @param Listener listener
	*/
	void RemovePointsAddedEventListener(AFeedTheTeddiesGameModeBase* Listener);

	/**
	 * Adds the given invoker as an invoker of the game over event
	 * @param Invoker invoker
	*/
	void AddGameOverEventInvoker(ABurgerPawn* Invoker);

	/**
	 * Removes the given invoker as an invoker of the game over event
	 * @param Invoker invoker
	*/
	void RemoveGameOverEventInvoker(ABurgerPawn* Invoker);

	/**
	 * Adds the given listener as a listener for the game over event
	 * @param Listener listener
	*/
	void AddGameOverEventListener(AFeedTheTeddiesGameModeBase* Listener);

	/**
	 * Removes the given listener as a listener for the game over event
	 * @param Listener listener
	*/
	void RemoveGameOverEventListener(AFeedTheTeddiesGameModeBase* Listener);

};
