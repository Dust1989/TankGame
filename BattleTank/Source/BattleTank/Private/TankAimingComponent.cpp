// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // TODO Should this really tick?

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelReference(class UTankBarrelComponent* BarrelToSet)
{
	if (BarrelToSet == nullptr) { return; }
	Barrel = BarrelToSet;
}


void UTankAimingComponent::SetTurretReference(class UTankTurretComponent* TurretToSet)
{
	if (TurretToSet == nullptr) { return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	FVector OutLaunchSpeed;
	if (Barrel == nullptr){ return;}

	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
			this,
			OutLaunchSpeed,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,	
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
	);


	if (bHaveAimSolution)
	{
		
		FVector AimDirection = OutLaunchSpeed.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);


	//FRotator TurretRotator = Turret->GetForwardVector().Rotation();
	//FRotator TurretDeltaRotator = AimRotator - TurretRotator;
	Turret->Turn(DeltaRotator.Yaw);

}

