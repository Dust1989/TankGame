// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UTankBarrelComponent* Barrel = nullptr;

	class UTankTurretComponent* Turret = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);
	
	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void Initial(class UTankBarrelComponent* BarrelToSet, class UTankTurretComponent* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	void MoveBarrelTowards(FVector AimDirection);

	float CalculateTurnAngle(float Value);

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000; //Sensible starting value of 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<class AProjectileActor> Projectile;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ReloadTimeInSecond = 3;

	double LastFireTime = 0;

};
