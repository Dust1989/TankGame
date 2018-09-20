// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"


class ATank;

/**
*
*/
UCLASS()
class BATTLETANK_API ATankController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "SetUp")
	void FoundAimingComponent(class UTankAimingComponent* TankAimComp);

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	bool GetSightRayHitLocation(FVector& HitLocation) const;
	
	void AimTowardsCrosshair();

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.3333;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	float LineTraceRange = 1000000;
};
