// Property of D4L4L

#include "TankTrack.h"




UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}



void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}


void UTankTrack::ApplySideWaysForce()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	/// Perpendicular velocity
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	/// Differentiating the velocity
	auto CorrectionAccelaration = -((SlippageSpeed / DeltaTime)*GetRightVector());

	/// TANK ROOT GETTER
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	/// f=m*a since 2 tracks divide by 2
	auto CorrectionForce = ((TankRoot->GetMass()) * CorrectionAccelaration) / 2;

	/// applying the force
	TankRoot->AddForce(CorrectionForce);
}


void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySideWaysForce();
	CurrentThrottle = 0;
}


void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	// #TODO Clamp Throttle
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();

	/// Cast as we cant add force to SceneComponent
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
