// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrelComponent.h"
#include "TankTurretComponent.h"
#include "ProjectileActor.h"

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

	if (AmmoAmount <= 0)
	{
		FiringState = EFiringState::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSecond)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else {
		FiringState = EFiringState::Locked;
	}
	
}

void UTankAimingComponent::Initial(class UTankBarrelComponent* BarrelToSet, class UTankTurretComponent* TurretToSet)
{
	if (!ensure(BarrelToSet != nullptr && TurretToSet != nullptr)) { return; }

	Barrel = BarrelToSet;
	Turret = TurretToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FVector OutLaunchSpeed;
	
	if (!ensure(Barrel)){ return;}

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
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Elevation is %f"), Elevation);	
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel != nullptr && Turret != nullptr)) { return; }

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);

	auto TurnAngle = CalculateTurnAngle(DeltaRotator.Yaw);
	Turret->Turn(TurnAngle);

	AimIntendDirection = AimDirection;
}

float UTankAimingComponent::CalculateTurnAngle(float Value)
{
	if (FMath::Abs(Value) > 180)
	{
		if (Value > 0)
		{
			return (Value - 360);
		}
		else
		{
			return (Value + 360);
		}
	}
	return Value;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	if (!ensure(Projectile)) { return; }

	if (FiringState != EFiringState::Reloading && FiringState != EFiringState::NoAmmo)
	{
		AProjectileActor* ProjectileActor = GetWorld()->SpawnActor<AProjectileActor>(
			Projectile,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		ProjectileActor->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();

		AmmoAmount--;
	}
}

int32 UTankAimingComponent::GetAmmoAmount() const
{
	return AmmoAmount;
}

EFiringState UTankAimingComponent::GetFireState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	FVector BarrelVector = Barrel->GetForwardVector();

	return !BarrelVector.Equals(AimIntendDirection, 0.01);
}