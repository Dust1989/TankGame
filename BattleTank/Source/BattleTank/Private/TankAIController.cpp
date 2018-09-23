// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = (GetWorld()->GetFirstPlayerController()->GetPawn());

	auto AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComp && PlayerTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius);

	AimingComp->AimAt(PlayerTank->GetActorLocation());

	if (AimingComp->GetFireState() == EFiringState::Locked)
	{
		AimingComp->Fire();
	}
}

