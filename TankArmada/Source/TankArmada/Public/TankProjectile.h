// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h "

#include "TankProjectile.generated.h"

UCLASS()
class TANKARMADA_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATankProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchProjectile(float Speed);

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	void OnTimerExpire();

	//UPROPERTY(VisibleAnywhere, Category = "Setup")
		UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UStaticMeshComponent* CollisonMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		URadialForceComponent* ImpactForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float DestroyDelay = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float ProjectileDamage = 20.0f;
};
