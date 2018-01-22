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
		UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *(HitLocation.ToString()));

		// #TODO Move barrel
	}

	
}


// Will ray trace
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	OutHitLocation = FVector(1.0);
	return true;

	// if hits terrain
		// update HitLocation
		//return true
	// else return false
}


