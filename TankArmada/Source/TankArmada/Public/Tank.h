// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
// ADD INCLUDES BELOW
#include "TankAimingComponent.h"
// ABOVE HERE
#include "Tank.generated.h"

class UTankBarrel; // Froward Declaration


UCLASS()
class TANKARMADA_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent* TankAimingComponent = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 100000; // #TODO Find Sensible Default
		
};
