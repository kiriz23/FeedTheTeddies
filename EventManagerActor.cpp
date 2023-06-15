// Copyright A.T. Chamillard. All Rights Reserved.

#include "EventManagerActor.h"

/**
 * Sets default values
*/
AEventManagerActor::AEventManagerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

/**
 * Called when the game starts or when spawned
*/
void AEventManagerActor::BeginPlay()
{
	Super::BeginPlay();
	
}

/**
 * Called every frame
 * @param DeltaTime Game time elapsed during last frame modified by the time dilation
*/
void AEventManagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/**
 * Adds the given invoker as an invoker of the points added event
 * @param Invoker invoker
*/
void AEventManagerActor::AddPointsAddedEventInvoker(AFriesActor* Invoker)
{
	// add new invoker and add all listeners for new invoker
	PointsAddedEventInvokers.Add(Invoker);
	for (auto& Element : PointsAddedEventListeners)
	{
		FDelegateHandle DelegateHandle = Element.Key->AddToPointsAddedEvent(
			Invoker->GetPointsAddedEvent());
		Element.Value.Add(Invoker, DelegateHandle);
	}
}

/**
 * Removes the given invoker as an invoker of the points added event
 * @param Invoker invoker
*/
void AEventManagerActor::RemovePointsAddedEventInvoker(AFriesActor* Invoker)
{
	// remove all listeners from invoker
	for (auto& Element : PointsAddedEventListeners)
	{
		if (Element.Value.Contains(Invoker))
		{
			Invoker->GetPointsAddedEvent().Remove(
				Element.Value[Invoker]);
			Element.Value.Remove(Invoker);
		}
	}

	// remove invoker
	PointsAddedEventInvokers.Remove(Invoker);
}

/**
 * Adds the given listener as a listener for the points added event
 * @param Listener listener
*/
void AEventManagerActor::AddPointsAddedEventListener(AFeedTheTeddiesGameModeBase* Listener)
{
	// add new listener and add new listener to all invokers
	PointsAddedEventListeners.Add(Listener);
	for (auto& Element : PointsAddedEventInvokers)
	{
		FDelegateHandle DelegateHandle = Listener->AddToPointsAddedEvent(
			Element->GetPointsAddedEvent());
		PointsAddedEventListeners[Listener].Add(Element, DelegateHandle);
	}
}

/**
 * Removes the given listener as a listener for the points added event
 * @param Listener listener
*/
void AEventManagerActor::RemovePointsAddedEventListener(AFeedTheTeddiesGameModeBase* Listener)
{
	// remove listener from all invokers
	for (auto& Element : PointsAddedEventInvokers)
	{
		if (PointsAddedEventListeners[Listener].Contains(Element))
		{
			Element->GetPointsAddedEvent().Remove(
				PointsAddedEventListeners[Listener][Element]);
			PointsAddedEventListeners[Listener].Remove(Element);
		}
	}

	// remove listener
	PointsAddedEventListeners.Remove(Listener);
}

/**
 * Adds the given invoker as an invoker of the game over event
 * @param Invoker invoker
*/
void AEventManagerActor::AddGameOverEventInvoker(ABurgerPawn* Invoker)
{
	// add new invoker and add all listeners for new invoker
	GameOverEventInvokers.Add(Invoker);
	for (auto& Element : GameOverEventListeners)
	{
		FDelegateHandle DelegateHandle = Element.Key->AddToGameOverEvent(
			Invoker->GetGameOverEvent());
		Element.Value.Add(Invoker, DelegateHandle);
	}
}

/**
 * Removes the given invoker as an invoker of the game over event
 * @param Invoker invoker
*/
void AEventManagerActor::RemoveGameOverEventInvoker(ABurgerPawn* Invoker)
{
	// remove all listeners from invoker
	for (auto& Element : GameOverEventListeners)
	{
		if (Element.Value.Contains(Invoker))
		{
			Invoker->GetGameOverEvent().Remove(
				Element.Value[Invoker]);
			Element.Value.Remove(Invoker);
		}
	}

	// remove invoker
	GameOverEventInvokers.Remove(Invoker);
}

/**
 * Adds the given listener as a listener for the game over event
 * @param Listener listener
*/
void AEventManagerActor::AddGameOverEventListener(AFeedTheTeddiesGameModeBase* Listener)
{
	// add new listener and add new listener to all invokers
	GameOverEventListeners.Add(Listener);
	for (auto& Element : GameOverEventInvokers)
	{
		FDelegateHandle DelegateHandle = Listener->AddToGameOverEvent(
			Element->GetGameOverEvent());
		GameOverEventListeners[Listener].Add(Element, DelegateHandle);
	}
}

/**
 * Removes the given listener as a listener for the game over event
 * @param Listener listener
*/
void AEventManagerActor::RemoveGameOverEventListener(AFeedTheTeddiesGameModeBase* Listener)
{
	// remove listener from all invokers
	for (auto& Element : GameOverEventInvokers)
	{
		if (GameOverEventListeners[Listener].Contains(Element))
		{
			Element->GetGameOverEvent().Remove(
				GameOverEventListeners[Listener][Element]);
			GameOverEventListeners[Listener].Remove(Element);
		}
	}

	// remove listener
	GameOverEventListeners.Remove(Listener);
}