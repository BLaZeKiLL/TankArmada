// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
// ADD INCLUDE"S HERE

#include "Engine/World.h"
// ABOVE HERE
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

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

protected:

	UFUNCTION(BlueprintCallable, Category = Setup)
		ATank * GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

private:

	// Start the tank moving the barrel so the shot would hit where
	// cross hair intersects the world
	void AimTowardsCrosshair();

	// Check For A Hit something Or SKY, return Hit Location
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	// Cross-Hair direction
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	// Ray-Cast
	bool GetLookVectorHitLocation(FVector LookDirection,FVector& OutHitLocation) const;

	/// UI X-factor
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float CrossHairXLocation = 0.5f;

	/// UI Y-factor
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float CrosshairYLocation = 0.3333f;

	// Max Shooting Range
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float ShootRange = 1000000.0f;
};
