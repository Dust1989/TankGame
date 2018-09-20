// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ProjectileActor.h"
#include "TankBarrelComponent.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::AimAt(FVector HitLocation)
{
	if (ensure(TankAimingComp)) {
		TankAimingComp->AimAt(HitLocation, LaunchSpeed);
	}
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool bCanFire = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSecond;

	if (Projectile && bCanFire)
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

