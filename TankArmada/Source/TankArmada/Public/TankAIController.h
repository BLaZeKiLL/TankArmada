// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
// ADD INCLUDES BELOW

#include "Engine/World.h"
// ABOVE HERE
#include "TankAIController.generated.h"

class UTankAimingComponent;

/**
 * AI Controller for the tank
 * CHECK THIS IS SELECTED AS THE AI CONTROLLER IN TANK BP
 */
UCLASS()
class TANKARMADA_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;


private:

	// How Close Can The AI Tank Come
	float AcceptanceRadius = 3000.0f; // Check Radius In cm
};
