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

	virtual void SetPawn(APawn* InPawn) override;

private:

	UFUNCTION()
		void OnPossessedTankDeath();


	// How Close Can The AI Tank Come
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 30.0f; // Check Radius In cm
};
