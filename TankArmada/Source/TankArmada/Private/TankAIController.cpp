// Property of D4L4L

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay(); // sets tick = true

	ATank* PossessedTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/// Always Aim at the Player
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

// Self Tank GETTER
ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

// Player Tank GETTER
ATank * ATankAIController::GetPlayerTank() const
{
	/// Failed cast returns a nullptr 
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
