// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector HitLocation);

protected:

	UPROPERTY(BlueprintReadWrite, Category = Movement)
	class UTankAimingComponent* TankAimingComp = nullptr;

	/*
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UTankMovementComponent* MovementComp;
	*/

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; //Sensible starting value of 1000 m/s

	class UTankBarrelComponent* Barrel;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AProjectileActor> Projectile;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ReloadTimeInSecond = 3;

	double LastFireTime = 0;


};
