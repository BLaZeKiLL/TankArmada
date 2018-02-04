// Property of D4L4L

#include "TankPlayerController.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/// Always aim at the Cross-hair
	AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector OutHitLocation; // OUT

	// If hit a valid Object (Ray-Cast)
	if (GetSightRayHitLocation(OutHitLocation))
	{
		// Aim at it
		AimingComponent->AimAt(OutHitLocation);
	}

}


// Returns the hit location of the projectile
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	/// Screen Location of the cross-hair
	FVector2D ScreenLocation = FVector2D((ViewportSizeX*CrossHairXLocation), (ViewportSizeY*CrosshairYLocation));

	/// Cross-Hair Direction
	FVector LookDirection;

	/// Unit-Vector in the direction we are looking
	if (GetLookDirection(ScreenLocation,LookDirection))
	{
		if (GetLookVectorHitLocation(LookDirection,OutHitLocation))
		{
			// Something is Hit
			return true;
		}

		// if nothing hit 0,0,0 is the HitLocation EG. sky
		return true;
	}
	
	/// Will never be reached as either we his something and Aim at it 
	/// Or we hit nothing and reset the Barrel
	// Still there for imaginary cases
	return false;
}


// Returns a unit vector pointing in player's look direction as a OUT parameter
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector & LookDirection) const
{
	FVector CameraLocation; //Obsolete

	// return the boolean value we get from DeprojectScreenPositionToWorld()
	return (DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraLocation,
		LookDirection
	));
}


// Ray-Trace along the look direction 
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection,FVector& OutHitLocation) const
{
	FHitResult OutHitResult; // OUT param
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); // START of the Ray-Cast
	auto EndLocation = StartLocation + (LookDirection * ShootRange); // END of the Ray-Cast

	/// Ray-Cast
	if (GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
		))
	{
		// Hit Something
		OutHitLocation = OutHitResult.Location;
		return true;
	}

	// Hit nothing e.g SKY
	/// Because of this 0 Vector , New Pitch Becomes 0 and Barrel Resets Itself
	OutHitLocation = FVector(0);
	return false;
}

