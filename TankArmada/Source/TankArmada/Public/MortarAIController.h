// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
// ADD INCLUDES BELOW
#include "Engine/World.h"
// ABOVE HERE
#include "MortarAIController.generated.h"

class UTankAimingComponent;

/**
 * Mortar AI Controller
 */
UCLASS()
class TANKARMADA_API AMortarAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	
};
