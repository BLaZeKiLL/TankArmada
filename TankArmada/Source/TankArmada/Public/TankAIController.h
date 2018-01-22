// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
// ADD INCLUDES BELOW
#include "Tank.h"
#include "Engine/World.h"
// ABOVE HERE
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKARMADA_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;
	
private:

	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;
};
