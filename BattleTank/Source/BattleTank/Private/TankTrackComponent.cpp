// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include "Components/StaticMeshComponent.h"

void UTankTrackComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GetOwner())) { return; }
	RootComp = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	OnComponentHit.AddDynamic(this, &UTankTrackComponent::OnHit);
}


void UTankTrackComponent::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}


void UTankTrackComponent::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FVector CorrectionAcceleration = SlippageSpeed / DeltaTime * -GetRightVector();

	FVector CorrectionForce = RootComp->GetMass() * CorrectionAcceleration / 2;

	RootComp->AddForce(CorrectionForce);
}

void UTankTrackComponent::DriveTank()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySidewaysForce();
	DriveTank();
	CurrentThrottle = 0;
}