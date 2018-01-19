// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();


	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) //Pointer Protection
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller NULLPTR !!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Player Controller Possessing : %s"), *(ControlledTank->GetName)());
	}
}


ATank * ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


