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

	/// Always Aim at the Player if in sight
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (PlayerInSight())
	{
		// #TODO which feels better aim when visible or aim always ?
		/// Always Aim at the Player if in sight
		//AimingComponent->AimAt(PlayerTank->GetActorLocation());
		
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

// Function for binding death delegate function
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
	/// Pass the references of start and end to utility functions
	FVector StartLocation, EndLocation;
	GetRayCastStartAndEnd(StartLocation, EndLocation);

	FHitResult OutHitResult;

	// Ignore Self as a Hit-Result for Line Trace
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(GetOwner());

	/// Line Trace
	if (GetWorld()->LineTraceSingleByChannel(
		OutHitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		CollisionParams
	))
	{
		if (OutHitResult.GetActor() == Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()))
		{
			// Player Visible
			return true;
		}
		else
		{
			// Player Not Visible
			return false;
		}
	}
	else
	{
		// Line Trace fail
		return false;
	}
}


void ATankAIController::GetRayCastStartAndEnd(FVector& StartLocation, FVector& EndLocation)
{
	// Location of the visible component on the AI tank
	StartLocation = Cast<USceneComponent>(
		(GetPawn()->GetComponentsByTag(USceneComponent::StaticClass(), FName("AI")))[0]
		)->GetComponentLocation();

	// Location of the visible component on the Player tank
	EndLocation = Cast<USceneComponent>(
		(GetWorld()->GetFirstPlayerController()->GetPawn()->GetComponentsByTag(USceneComponent::StaticClass(), FName("AI")))[0]
		)->GetComponentLocation();
}