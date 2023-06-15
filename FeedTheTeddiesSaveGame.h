// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "FeedTheTeddiesSaveGame.generated.h"

/**
 * Class for saving and retrieving gameplay data
 */
UCLASS()
class FEEDTHETEDDIES_API UFeedTheTeddiesSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, Category = "Saved Game Data")
		int HighScore;
	UPROPERTY(BlueprintReadWrite, Category = "Saved Game Data")
		int Difficulty;
};
