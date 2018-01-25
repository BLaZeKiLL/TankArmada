// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKARMADA_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// -1 max down speed, +1 max up speed
	void Elevate(float RelativeSpeed);
	
private:
	
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20.0f; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevation = 40.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation = 0.0f;
	
};
