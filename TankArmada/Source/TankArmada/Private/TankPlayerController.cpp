// Property of D4L4L

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) //Pointer Protection
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller NULLPTR !!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller Possessing : %s"), *(ControlledTank->GetName)());
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("Tick"));

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
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction : %s"), *(HitLocation.ToString()));

		// #TODO Move barrel
	}

	
}


// Will ray trace
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D((ViewportSizeX*CrossHairXLocation), (ViewportSizeY*CrosshairYLocation));
	UE_LOG(LogTemp, Warning, TEXT("Screen location : %s"), *(ScreenLocation.ToString()));

	// find cross-hair position
	// de-project the location
	// line trace through the position
	// if hits terrain
		// update HitLocation
		//return true
	// else return false
	
	
	return true;
}


