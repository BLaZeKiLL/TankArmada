// Property of D4L4L

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointer as it is in constructor
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));


}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Delegates Aiming to TankAimingComponent with a LaunchSpeed
void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


// Barrel SETTER
void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

// Turret SETTER
void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}


void ATank::Fire()
{
	bool bIsReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds;

	if (Barrel && bIsReloaded && ProjectileBlueprint) 
	{

		auto Projectile = GetWorld()->SpawnActor<ATankProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("FiringHole")),
			Barrel->GetSocketRotation(FName("FiringHole"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile Blueprint Missing"));
	}
}
