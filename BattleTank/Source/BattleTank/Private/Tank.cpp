// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComp = CreateDefaultSubobject<UTankAimingComponent>(TEXT("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::SetBarrelReference(UTankBarrelComponent* BarrelToSet)
{
	TankAimingComp->SetBarrelReference(BarrelToSet);
}

void ATank::AimAt(FVector HitLocation)
{
	if (TankAimingComp)
	{
		TankAimingComp->AimAt(HitLocation, LaunchSpeed);
	}	
}

