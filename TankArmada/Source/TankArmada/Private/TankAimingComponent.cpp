// Property of D4L4L

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "TankProjectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	/// First fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}


void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	/// Firing Status Checker

	if (Ammo == 0)
	{
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds))
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("FiringHole"));

	/// calculate whether it is possible to shoot the projectile with given speed
	/// parabolic path 2-D projectile motion
	bool bAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0f,
		0.0f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	/// We remove hit location from IF as when we collide with the sky we get solution with hit location 0,0,0 
	/// so pitch becomes 0 and turret resets itself
	if (bAimSolution && HitLocation != FVector(0)) 
	{
		/// Unit Vector
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		/// Delegate to MoveBarrelTowards
		MoveBarrelTowards(AimDirection);

	}

}


void UTankAimingComponent::Fire()
{

	if (FiringStatus != EFiringStatus::Reloading && FiringStatus != EFiringStatus::OutOfAmmo)
	{
		/// Pointer protection
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }

		/// Spawn Transform Of Projectile
		auto Projectile = GetWorld()->SpawnActor<ATankProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("FiringHole")),
			Barrel->GetSocketRotation(FName("FiringHole"))
			);

		/// Launch Projectile
		Projectile->LaunchProjectile(LaunchSpeed);

		Ammo--;

		/// Set Launch Time for reloading (UI)
		LastFireTime = FPlatformTime::Seconds();
	}

}


void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

int32 UTankAimingComponent::GetAmmo() const
{
	return Ammo;
}


bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	/// Compare the barrel and aim direction
	return !(Barrel->GetForwardVector().Equals(AimDirection, 0.01f));
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	/// The new angle for the barrel
	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) > 180.F)
	{
		DeltaRotator.Yaw *= -1.F;
	}
	Turret->Rotate(DeltaRotator.Yaw);
}


EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}
