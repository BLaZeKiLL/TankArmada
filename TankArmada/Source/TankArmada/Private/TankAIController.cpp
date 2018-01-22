// Property of D4L4L

#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	ATank* PossessedTank = GetControlledTank();
	ATank* PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		// UE_LOG(LogTemp, Warning, TEXT("Error : AI failed to posses ! OR"));
		UE_LOG(LogTemp, Warning, TEXT("Error : Player Not found !"));
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller Possessing : %s"), *(PossessedTank->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("Tank looking at : %s"), *(PlayerTank->GetName()));
	}
}


ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


ATank * ATankAIController::GetPlayerTank() const
{
	/// Failed cast returns a nullptr 
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}
