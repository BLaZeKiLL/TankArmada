// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
// ADD INCLUDE"S HERE
#include "Tank.h"
// ABOVE HERE
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKARMADA_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	ATank * GetControlledTank() const;
	
	void BeginPlay() override;
};
