// Property of D4L4L

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // NEEDE FOR BLUEPRINT BEGIN PLAY TO WORK
	
}


void ATank::Fire()
{
	bool bIsReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeInSeconds;

	/// Pointer protection
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }

	if (bIsReloaded) 
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
