// Property of D4L4L

#include "TankBarrel.h"



// Barrel Movement
void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed,-1.0f,+1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	/// Clamps the value between specified limits
	auto Elevation = FMath::Clamp<float>(RawNewElevation,MinElevation,MaxElevation);

	//Set new Angle
	SetRelativeRotation(FRotator(Elevation, 0.0f, 0.0f));
}
