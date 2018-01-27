// Property of D4L4L

#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle)
{

	// #TODO Clamp Throttle
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	/// Cast as we cant add force to SceneComponent
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied,ForceLocation);
}
