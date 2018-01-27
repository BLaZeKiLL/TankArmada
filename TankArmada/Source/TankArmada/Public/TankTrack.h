// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
// ADD INCLUDES BELOW
#include "Engine/World.h"

// ABOVE HERE
#include "TankTrack.generated.h"

/**
 * Driving Force to the Tracks is Applied through this component
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKARMADA_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	// Set Throttle Between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
		void SetThrottle(float Throttle);
	
	// Max Force Per Track In Newtons
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float TrackMaxDrivingForce = 40000000.0f; // this is 400,000 N of force unit of measurement in UE is cm
};
