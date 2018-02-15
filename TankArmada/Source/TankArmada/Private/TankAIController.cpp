// Property of D4L4L

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

// Dependant on Movement Component through path finding

void ATankAIController::BeginPlay()
{
	Super::BeginPlay(); // sets tick = true
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// This In Tick As AI or Player Tank may die
	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	/// DOUBLE CHECK ensure() MACRO
	if (!ensure(PlayerTank && ControlledTank && AimingComponent)) { return; }
	
	MoveTowardsPlayer(PlayerTank, AcceptanceRadius);

	if (PlayerInSight())
	{

		/// Always Aim at the Player if in sight
		AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
		/// Fire at the Player if locked
		if ((AimingComponent->GetFiringStatus() == EFiringStatus::Locked))
		{
			AimingComponent->Fire();
		}
	} 
}

/// Uses MoveToActor of AIController class
/// Using NavMesh
void ATankAIController::MoveTowardsPlayer(APawn * PlayerTank, float DynamicAcceptanceRadius)
{
	/// Movement Component Dependency
	MoveToActor(
		PlayerTank,
		DynamicAcceptanceRadius
	);
}


void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);

		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}


void ATankAIController::OnPossessedTankDeath()
{
	GetPawn()->DetachFromControllerPendingDestroy();
}

// Checks whether the player is in sight or not
bool ATankAIController::PlayerInSight()
{
	auto AIRayCast = Cast<USceneComponent>((GetPawn()->GetComponentsByTag(USceneComponent::StaticClass(), FName("AI")))[0]);
	auto StartLocation = AIRayCast->GetComponentLocation();
	auto EndLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FHitResult OutHitResult;

	if (GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	))
	{
		if (OutHitResult.GetActor() == Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

