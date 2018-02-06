// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// ADD INCLUDES BELOW
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
// ABOVE
#include "TankAimingComponent.generated.h"

// Froward Declaration
class UTankBarrel;
class UTankTurret;
class ATankProjectile;

UENUM()
enum class EFiringStatus : uint8
{
	// YELLOW
	Aiming,
	// RED
	Reloading,
	// GREEN
	Locked
};


// Holds barrel's Properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKARMADA_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	//Delegate Aiming
	void AimAt(FVector HitLocation);

	// Fire the projectile 
	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	// Tick
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	// BeginPlay
	void BeginPlay() override;

protected:

	// Status for the UI
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;

	// SETTER
	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

private:

	// Launch Speed of the projectile
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000.0f;

	// Projectile Blueprint Reference
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		TSubclassOf<ATankProjectile> ProjectileBlueprint;

	// Reload Time
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3.0f;

	// Barrel of the tank
	UTankBarrel * Barrel = nullptr;
	
	// Turret of the tank
	UTankTurret * Turret = nullptr;

	// UI true = yellow
	bool IsBarrelMoving();

	// Aiming : Barrel Movement
	void MoveBarrelTowards(FVector AimDirection);

	// UI : compared with reload time for firing status
	double LastFireTime = 0;

	// UI : compared with current barrel direction to check for movement
	FVector AimDirection;
};
