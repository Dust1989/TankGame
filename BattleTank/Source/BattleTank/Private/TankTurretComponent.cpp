// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"




void UTankTurretComponent::Turn(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto TurnChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float RawNewTurn = RelativeRotation.Yaw + TurnChange;

	SetRelativeRotation(FRotator(0, RawNewTurn, 0));
}
