// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	auto PossessPawn = Cast<ATank>(InPawn);
	if (!ensure(PossessPawn)) { return; }

	PossessPawn->OnDead.AddDynamic(this, &ATankAIController::OnDead);
}

void ATankAIController::OnDead()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}

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

