// Property of D4L4L

#include "TankPlayerController.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) //Pointer Protection
	{
		//UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller NULLPTR !!"));
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller Possessing : %s"), *(ControlledTank->GetName)());
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // OUT

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);

		// #TODO Move barrel
	}

	
}


// Returns the hit location of the projectile
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	/// Screen Location of the cross-hair
	FVector2D ScreenLocation = FVector2D((ViewportSizeX*CrossHairXLocation), (ViewportSizeY*CrosshairYLocation));

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
	auto StartLocation = PlayerCameraManager->GetCameraLocation(); // START
	auto EndLocation = StartLocation + (LookDirection * ShootRange); // END

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

	// Hit nothing
	OutHitLocation = FVector(0);
	return false;
}

