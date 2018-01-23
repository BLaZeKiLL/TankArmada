// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
// ADD INCLUDE"S HERE
#include "Tank.h"
#include "Engine/World.h"
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

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection,FVector& OutHitLocation) const;

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
		float CrosshairYLocation = 0.3333;

	UPROPERTY(EditAnywhere)
		float ShootRange = 1000000.0;
};
