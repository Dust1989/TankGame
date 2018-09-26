// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto TankName = GetOwner()->GetName();
	FVector MoveIntention = MoveVelocity.GetSafeNormal();
	FVector ForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(ForwardVector, MoveIntention);

	auto RightThrow = FVector::CrossProduct(ForwardVector, MoveIntention);

	MoveRight(RightThrow.Z);

	MoveForward(ForwardThrow);
}

void UTankMovementComponent::MoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::MoveRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }

	if (Throw > 0)
	{
		LeftTrack->SetThrottle(Throw);
		RightTrack->SetThrottle(-Throw/3);
	}
	else
	{
		RightTrack->SetThrottle(-Throw);
		LeftTrack->SetThrottle(Throw/3);
	}
}

void UTankMovementComponent::InitialTankTrack(class UTankTrackComponent* LeftTrackToSet, class UTankTrackComponent* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}
