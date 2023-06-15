// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BurgerPlayerController.generated.h"

/**
 * A burger player controller
 */
UCLASS()
class FEEDTHETEDDIES_API ABurgerPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widgets")
		TSubclassOf<UUserWidget> PauseMenuWidgetClass;

public:
	/**
	 * Called to bind functionality to input
	*/
	virtual void SetupInputComponent() override;

	/**
	 * Moves the burger horizontally
	 * @param input input on Horizontal axis
	*/
	void MoveHorizontally(float input);

	/**
	 * Moves the burger vertically
	 * @param input input on Vertical axis
	*/
	void MoveVertically(float input);

	/**
	 * Shoots french fries
	*/
	void Shoot();

private:
	/**
	 * Pauses the game
	*/
	void PauseGame();
};
