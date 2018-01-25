// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
// ADD INCLUDES BELOW

// ABOVE HERE
#include "Tank.generated.h"

class UTankBarrel; // Froward Declaration
class UTankAimingComponent;

UCLASS()
class TANKARMADA_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);
	 
	/// SOFT REFRENCING the Barrel Asset Contained in a Component Class
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	// Speed At which Projectile is launched used in calculating the path solution
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000.0f; // #TODO Find Sensible Default
		
};
