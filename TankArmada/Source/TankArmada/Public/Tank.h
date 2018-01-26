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
	 
	/// SOFT REFRENCING the Barrel Asset Contained in a Component Class
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void Fire();

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
		float LaunchSpeed = 4000.0f; 
		
	UPROPERTY(EditAnywhere, Category = Firing)
		TSubclassOf<ATankProjectile> ProjectileBlueprint;

	// local barrel for Spawning Projectile
	UTankBarrel* Barrel = nullptr;
};
