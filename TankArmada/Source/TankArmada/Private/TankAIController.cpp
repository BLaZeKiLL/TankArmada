// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	ATank* PossessedTank = GetControlledTank();
	if (!PossessedTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Error : AI failed to posses !"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank AI Controller Possessing : %s"), *(PossessedTank->GetName)());
	}
}

ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}