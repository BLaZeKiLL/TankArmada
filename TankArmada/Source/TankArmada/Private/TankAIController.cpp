// Property of D4L4L

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay(); // sets tick = true
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PossessedTank = Cast<ATank>(GetPawn());
	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (PlayerTank && PossessedTank) // Pointer Protection
	{
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

