// Property of D4L4L

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // NEEDE FOR BLUEPRINT BEGIN PLAY TO WORK
	
	CurrentHealth = StartingHealth;
}


float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	
	int32 DamageToApply = FMath::Clamp(FPlatformMath::RoundToInt(DamageAmount), 0, CurrentHealth);
	
	CurrentHealth -= DamageToApply;
	if (CurrentHealth <=0)
	{
		OnDeath.Broadcast();
	}

	return DamageToApply;
}


float ATank::GetPercentHealth()
{
	return (float)CurrentHealth / (float)StartingHealth;
}


void ATank::RestoreHealth()
{
	CurrentHealth = StartingHealth;
}

