// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"




void UTankTrackComponent::SetThrottle(float Throttle)
{
	FString TrackName = GetName();

	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
