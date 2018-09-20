// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "DrawDebugHelpers.h"
#include "TankAimingComponent.h"


void ATankController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComp)) { return; }
	FoundAimingComponent(AimingComp);

}

void ATankController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}


bool ATankController::GetSightRayHitLocation(FVector& HitLocation) const
{

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY *CrosshairYLocation);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		GetLookVectorHitLocation(LookDirection, HitLocation);		
	}
	
	return true;

}

void ATankController::AimTowardsCrosshair()
{
	if (!GetPawn()){ return;}

	auto AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComp)) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{

		//UE_LOG(LogTemp, Warning, TEXT("HitLocation is %s"), *HitLocation.ToString());
		DrawDebugSphere(GetWorld(), HitLocation, 50.f, 20, FColor::Green, false, 0.5f, 0, 1.f);

		AimingComp->AimAt(HitLocation);
	}

}

bool ATankController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const 
{
	FHitResult Hit;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();

	//test the difference between two direction
	//LookDirection = PlayerCameraManager->GetCameraRotation().Vector();

	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;

	
	if (GetWorld()->LineTraceSingleByChannel(
		Hit, 
		StartLocation, 
		EndLocation, 
		ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = Hit.Location;
		return true;
	}
	else
	{
		HitLocation = FVector::ZeroVector;
		return false;
	}
	
}
