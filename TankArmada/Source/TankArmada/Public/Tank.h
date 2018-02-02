// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
// ADD INCLUDES BELOW
#include "Engine/World.h"

// ABOVE HERE
#include "Tank.generated.h"

// Froward Declaration
class UTankBarrel;
class UTankTurret;
class UTankAimingComponent;
class ATankProjectile;

UCLASS()
class TANKARMADA_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);
	 

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		UTankAimingComponent* TankAimingComponent = nullptr;

private:

	// Speed At which Projectile is launched used in calculating the path solution
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.0f; 
	
	/// ANY CHANGES TO THE CLASS CAUSE THIS TO RESET IN THE BLUEPRINT
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<ATankProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.0f;

	// local barrel for Spawning Projectile
	UTankBarrel* Barrel = nullptr; // #TODO Remove

	double LastFireTime = 0;
};
