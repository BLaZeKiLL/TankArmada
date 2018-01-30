// Property of D4L4L

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	UE_LOG(LogTemp, Warning, TEXT("GOKU :%s Tank Counstructed !"), *GetName());
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // NEEDE FOR BLUEPRINT BEGIN PLAY TO WORK
	
	UE_LOG(LogTemp, Warning, TEXT("GOKU : %s Tank Begin Play !"), *GetName());
}


// Delegates Aiming to TankAimingComponent with a LaunchSpeed
void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }

	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
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

}
