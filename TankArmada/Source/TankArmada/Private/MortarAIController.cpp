// Property of D4L4L

#include "MortarAIController.h"
#include "TankAimingComponent.h"



void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMortarAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// This In Tick As AI or Player Tank may die
	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledMortar = GetPawn();
	auto AimingComponent = ControlledMortar->FindComponentByClass<UTankAimingComponent>();

	/// DOUBLE CHECK ensure() MACRO
	if (!ensure(PlayerTank && ControlledMortar && AimingComponent)) { return; }

	/// Always Aim at the Player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	/// Fire at the Player if locked
	if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		AimingComponent->Fire();
	}
}
