// Property of D4L4L

#include "TankAIController.h"
#include "TankAimingComponent.h"

// Dependant on Movement Component through path finding

void ATankAIController::BeginPlay()
{
	Super::BeginPlay(); // sets tick = true
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	//APawn* PossessedTank = (GetPawn());
	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	/// DOUBLE CHECK ensure() MACRO
	if (!ensure(PlayerTank && ControlledTank && AimingComponent)) { return; }
	
	/// Movement Component Dependency
	MoveToActor(
		PlayerTank,
		AcceptanceRadius 
		);
		
	/// Always Aim at the Player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());
	
	/// Fire at the Player
	AimingComponent->Fire();
}

