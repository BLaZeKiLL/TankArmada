// Property of D4L4L

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
// ADD INCLUDES BELOW
#include "Engine/World.h"

// ABOVE HERE
#include "Tank.generated.h"

UCLASS()
class TANKARMADA_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
