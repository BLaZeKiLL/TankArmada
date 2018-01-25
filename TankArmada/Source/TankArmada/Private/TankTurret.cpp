// Property of D4L4L

#include "TankTurret.h"




void UTankTurret::Rotate(float RelativeSpeed)
{
	auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1.0f, +1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0.0f, Rotation, 0.0f));
}
