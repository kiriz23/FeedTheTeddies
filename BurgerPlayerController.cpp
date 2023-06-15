// Copyright A.T. Chamillard. All Rights Reserved.

#include "BurgerPlayerController.h"

#include "BurgerPawn.h"

/**
 * Called to bind functionality to input
*/
void ABurgerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// set up movement key bindings
	check(InputComponent != nullptr);
	InputComponent->BindAxis("Horizontal",
		this,
		&ABurgerPlayerController::MoveHorizontally);
	InputComponent->BindAxis("Vertical",
		this,
		&ABurgerPlayerController::MoveVertically);

	// set up shoot key binding
	InputComponent->BindAction("Shoot",
		EInputEvent::IE_Pressed, this,
		&ABurgerPlayerController::Shoot);

	// set up pause key binding
	InputComponent->BindAction("PauseGame",
		EInputEvent::IE_Pressed, this,
		&ABurgerPlayerController::PauseGame);
}

/**
 * Moves the burger horizontally
 * @param input input on Horizontal axis
*/
void ABurgerPlayerController::MoveHorizontally(float input)
{
	if (input != 0)
	{
		ABurgerPawn* BurgerPawn =
			(ABurgerPawn*)GetPawn();
		if (BurgerPawn != nullptr)
		{
			BurgerPawn->MoveHorizontally(input);
		}
	}
}

/**
 * Moves the burger vertically
 * @param input input on Vertical axis
*/
void ABurgerPlayerController::MoveVertically(float input)
{
	if (input != 0)
	{
		ABurgerPawn* BurgerPawn =
			(ABurgerPawn*)GetPawn();
		if (BurgerPawn != nullptr)
		{
			BurgerPawn->MoveVertically(input);
		}
	}
}

/**
 * Shoots french fries
*/
void ABurgerPlayerController::Shoot()
{
	ABurgerPawn* BurgerPawn =
		(ABurgerPawn*)GetPawn();
	if (BurgerPawn != nullptr)
	{
		BurgerPawn->Shoot();
	}
}

/**
 * Pauses the game
*/
void ABurgerPlayerController::PauseGame()
{
	if (PauseMenuWidgetClass != nullptr)
	{
		UUserWidget* CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass);
		if (CurrentWidget != nullptr)
		{
			// add pause menu and pause game
			CurrentWidget->AddToViewport();
			SetInputMode(FInputModeUIOnly());
			bShowMouseCursor = true;
			SetPause(true);
		}
	}
}