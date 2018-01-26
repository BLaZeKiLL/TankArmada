// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/World.h"
#include "GameFramework/ProjectileMovementComponent.h"

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

	UProjectileMovementComponent * ProjectileMovementComponent = nullptr;
	
};