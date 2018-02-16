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

	// Nav-Mesh Movement
	void MoveTowardsPlayer(APawn * PlayerTank, float DynamicAcceptanceRadius);

	virtual void SetPawn(APawn* InPawn) override;

private:

	UFUNCTION()
		void OnPossessedTankDeath();

	// How Close Can The AI Tank Come
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 7500.0f; // Check Radius In cm

	// Checks whether the player is in sight or not
	bool PlayerInSight();

	// Helper function for Player in Sight Ray-cast
	void GetRayCastStartAndEnd(FVector& StartLocation, FVector& EndLocation);
};
