// Copyright A.T. Chamillard. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DelegateDeclarations.generated.h"

// points added event
DECLARE_MULTICAST_DELEGATE_OneParam(FPointsAddedEvent, int);

// game over event
DECLARE_MULTICAST_DELEGATE(FGameOverEvent);

/**
 * Container for delegate declarations
 */
UCLASS()
class FEEDTHETEDDIES_API UDelegateDeclarations : public UObject
{
	GENERATED_BODY()
	
};
