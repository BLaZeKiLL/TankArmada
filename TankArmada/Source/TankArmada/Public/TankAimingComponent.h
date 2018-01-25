// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
// ADD INCLUDES BELOW
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
// ABOVE
#include "TankAimingComponent.generated.h"

// Froward Declaration
class UTankBarrel; 

// Holds barrel's Properties
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKARMADA_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation, float LaunchSpeed);

	void SetBarrelReference(UTankBarrel* BarrelToSet);

	// #TODO SetTurretReference()

private:

	UTankBarrel * Barrel = nullptr;
	
	void MoveBarrelTowards(FVector AimDirection);
};
