// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
//ADD INCLUDES BELOW
#include "Tank.h"


#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class TANKARMADA_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	ATank * GetControlledTank() const;

	void BeginPlay() override;
	
	
};
