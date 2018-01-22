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
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	ATank * GetControlledTank() const;

	// Start the tank moving the barrel so the shot would hit where
	// cross hair intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;
};
