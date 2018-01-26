// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/World.h"

#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKARMADA_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void Rotate(float RelativeSpeed);
	
	// Rate of change of angle
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 25.0f;
	
};
