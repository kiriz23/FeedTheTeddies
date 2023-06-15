// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainMenuActor.generated.h"

/**
 * An actor for the main menu. The only purpose of this actor
 * is to make sure we have a valid save game so we don't have 
 * to do extra Blueprint coding in the difficulty menu
*/
UCLASS()
class FEEDTHETEDDIES_API AMainMenuActor : public AActor
{
	GENERATED_BODY()
	
public:	
	/**
	 * Sets default values for this actor's properties
	*/
	AMainMenuActor();

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
