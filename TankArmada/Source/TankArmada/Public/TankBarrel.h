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

	void Elevate(float DegreesPerSecond);
	
private:
	
	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegreesPerSecond = 20; 

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevation = 40;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevation = 0;
	
};
