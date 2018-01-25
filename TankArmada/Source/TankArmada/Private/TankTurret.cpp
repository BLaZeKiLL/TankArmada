// Property of D4L4L

#include "TankTurret.h"




void UTankTurret::Rotate(float RelativeSpeed)
{
	auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1.0f, +1.0f) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = RelativeRotation.Yaw + RotationChange;

	auto Rotaion = FMath::Clamp<float>(RawNewRotation, -360.0f, +360.0f);

	SetRelativeRotation(FRotator(0.0f, RawNewRotation, 0.0f));
}
