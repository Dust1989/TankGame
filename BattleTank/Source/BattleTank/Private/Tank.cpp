// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ProjectileActor.h"
#include "TankBarrelComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComp = CreateDefaultSubobject<UTankAimingComponent>(TEXT("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrelComponent* BarrelToSet)
{
	TankAimingComp->SetBarrelReference(BarrelToSet);

	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurretComponent* BarrelToSet)
{
	TankAimingComp->SetTurretReference(BarrelToSet);
}

void ATank::AimAt(FVector HitLocation)
{
	if (TankAimingComp)
	{
		TankAimingComp->AimAt(HitLocation, LaunchSpeed);
	}	
}

void ATank::Fire()
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Firing...."), Time);

	bool bCanFire = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecond;

	if (Projectile && Barrel && bCanFire)
	{
		AProjectileActor* ProjectileActor = GetWorld()->SpawnActor<AProjectileActor>(
								Projectile, 
								Barrel->GetSocketLocation(FName("Projectile")), 
								Barrel->GetSocketRotation(FName("Projectile"))
								);

		ProjectileActor->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

