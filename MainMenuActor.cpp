// Copyright A.T. Chamillard. All Rights Reserved.


#include "MainMenuActor.h"

#include "Kismet/GameplayStatics.h"
#include "FeedTheTeddiesSaveGame.h"

/**
 * Sets default values
*/
AMainMenuActor::AMainMenuActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

/**
 * Called when the game starts or when spawned
*/
void AMainMenuActor::BeginPlay()
{
	Super::BeginPlay();
	
	// try to load saved game
	UFeedTheTeddiesSaveGame* SaveGameInstance = Cast<UFeedTheTeddiesSaveGame>(
		UGameplayStatics::LoadGameFromSlot(
			"FeedTheTeddiesSaveSlot", 0));
	if (SaveGameInstance == nullptr)
	{
		// couldn't load saved game
		SaveGameInstance = Cast<UFeedTheTeddiesSaveGame>(
			UGameplayStatics::CreateSaveGameObject(
				UFeedTheTeddiesSaveGame::StaticClass()));
	}

	// development use only; reset saved high score to 0
	// comment out when not needed
	//UFeedTheTeddiesSaveGame* SaveGameInstance = Cast<UFeedTheTeddiesSaveGame>(
	//	UGameplayStatics::CreateSaveGameObject(
	//		UFeedTheTeddiesSaveGame::StaticClass()));
	//SaveGameInstance->HighScore = 0;
	//SaveGameInstance->Difficulty = 0;
	//UGameplayStatics::SaveGameToSlot(SaveGameInstance,
	//	"FeedTheTeddiesSaveSlot", 0);
}

/**
 * Called every frame
 * @param DeltaTime Game time elapsed during last frame modified by the time dilation
*/
void AMainMenuActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

