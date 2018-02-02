// Property of D4L4L

#include "TankAIController.h"
#include "Tank.h"

// Dependant on Movement Component through path finding

void ATankAIController::BeginPlay()
{
	Super::BeginPlay(); // sets tick = true
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PossessedTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	/// DOUBLE CHECK ensure() MACRO
	if (!ensure(PlayerTank && PossessedTank))
	{
		return; // Pointer Protection
	}
	else
	{
		/// Movement Component Dependency
		MoveToActor(
			PlayerTank,
			AcceptanceRadius 
			);


		/// Always Aim at the Player
		PossessedTank->AimAt(PlayerTank->GetActorLocation());
		/// Then Blast That MOTHERFUCKAAA
		PossessedTank->Fire(); 
	}

}

