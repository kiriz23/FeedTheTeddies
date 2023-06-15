// Copyright Epic Games, Inc. All Rights Reserved.

#include "FeedTheTeddiesGameModeBase.h"

#include "Kismet/GameplayStatics.h"
#include "EventManagerActor.h"
#include "ConfigurationDataActor.h"
#include "FeedTheTeddiesSaveGame.h"

/**
 * Sets default values for this game mode's properties
*/
AFeedTheTeddiesGameModeBase::AFeedTheTeddiesGameModeBase()
{
	// set pawn and player controller
	ConstructorHelpers::FObjectFinder<UClass>
		PawnClass(TEXT("Class'/Game/FeedTheTeddies/Blueprints/BP_BurgerPawn.BP_BurgerPawn_C'"));
	if (PawnClass.Object != nullptr)
	{
		DefaultPawnClass = PawnClass.Object;
	}
	ConstructorHelpers::FObjectFinder<UClass>
		ControllerClass(TEXT("Class'/Game/FeedTheTeddies/Blueprints/BP_BurgerPlayerController.BP_BurgerPlayerController_C'"));
	if (ControllerClass.Object != nullptr)
	{
		PlayerControllerClass = ControllerClass.Object;
	}
}

/**
 * Called when the game starts or when spawned
*/
void AFeedTheTeddiesGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// add to event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);
		EventManager->AddPointsAddedEventListener(this);
		EventManager->AddGameOverEventListener(this);
	}

	// add hud
	if (HudWidgetClass != nullptr)
	{
		UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HudWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}

	// start timer
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "ConfigurationData", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AConfigurationDataActor* ConfigurationData = 
			Cast<AConfigurationDataActor>(TaggedActors[0]);
		SecondsLeft = ConfigurationData->GetTotalGameSeconds();
		StartOneSecondTimer();
	}
}

/**
 * Adds points to the score
 * @param Points points to add to score
*/
void AFeedTheTeddiesGameModeBase::AddPoints(int Points)
{
	Score += Points;
}

/**
 * Adds this object to the given points added event
 * @param PointsAddedEvent points added event
 * @return delegate handle
*/
FDelegateHandle AFeedTheTeddiesGameModeBase::AddToPointsAddedEvent(FPointsAddedEvent& PointsAddedEvent)
{
	return PointsAddedEvent.AddUObject(this,
		&AFeedTheTeddiesGameModeBase::AddPoints);
}

/**
 * Ends the game
*/
void AFeedTheTeddiesGameModeBase::EndGame()
{
	// try to load saved game
	int HighScore = 0;
	UFeedTheTeddiesSaveGame* SaveGameInstance = Cast<UFeedTheTeddiesSaveGame>(
		UGameplayStatics::LoadGameFromSlot(
			"FeedTheTeddiesSaveSlot", 0));

	// we know the main menu guarantees there's a saved game,
	// but do this to be safe in case that changes
	if (SaveGameInstance != nullptr)
	{
		HighScore = SaveGameInstance->HighScore;
	}

	// check for and save new high score
	if (Score > HighScore)
	{
		// we know the main menu guarantees there's a saved game,
		// but do this to be safe in case that changes
		if (SaveGameInstance == nullptr)
		{
			// couldn't load saved game
			SaveGameInstance = Cast<UFeedTheTeddiesSaveGame>(
				UGameplayStatics::CreateSaveGameObject(
					UFeedTheTeddiesSaveGame::StaticClass()));
		}
		SaveGameInstance->HighScore = Score;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance,
			"FeedTheTeddiesSaveSlot", 0);
	}

	// display game over widget and pause game
	if (GameOverWidgetClass != nullptr)
	{
		UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass);
		if (CurrentWidget != nullptr)
		{
			// add game over widget and pause game
			CurrentWidget->AddToViewport();
			APlayerController* PlayerController =
				GetWorld()->GetFirstPlayerController();
			if (PlayerController != nullptr)
			{
				PlayerController->SetInputMode(FInputModeUIOnly());
				PlayerController->bShowMouseCursor = true;
				PlayerController->SetPause(true);
			}
		}
	}
}

/**
 * Adds this object to the given game over event
 * @param GameOverEvent game over event
 * @return delegate handle
*/
FDelegateHandle AFeedTheTeddiesGameModeBase::AddToGameOverEvent(FGameOverEvent& GameOverEvent)
{
	return GameOverEvent.AddUObject(this,
		&AFeedTheTeddiesGameModeBase::EndGame);
}

/**
 * Called when actor is being removed from level
 * @param EndPlayReason why the actor is being removed
*/
void AFeedTheTeddiesGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// remove from event manager
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(
		GetWorld(), "EventManager", TaggedActors);
	if (TaggedActors.Num() > 0)
	{
		AEventManagerActor* EventManager = Cast<AEventManagerActor>(
			TaggedActors[0]);

		// remove as listener for points added and game over events
		EventManager->RemovePointsAddedEventListener(this);
		EventManager->RemoveGameOverEventListener(this);
	}
}

/**
 * Starts a one second timer
*/
void AFeedTheTeddiesGameModeBase::StartOneSecondTimer()
{
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this,
		&AFeedTheTeddiesGameModeBase::ChangeSecondsLeft,
		1.0f);
}

/**
 * Changes displayed second left
 * @param NewSecondsLeft new seconds left
*/
void AFeedTheTeddiesGameModeBase::ChangeSecondsLeft()
{
	SecondsLeft -= 1;

	// check for game over
	if (SecondsLeft == 0)
	{
		EndGame();
	}
	else
	{
		StartOneSecondTimer();
	}
}