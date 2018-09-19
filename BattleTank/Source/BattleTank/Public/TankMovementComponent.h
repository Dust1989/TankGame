// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
private:
	class UTankTrackComponent* LeftTrack;
	class UTankTrackComponent* RightTrack;

	// Use this function to find the Tank turn Vector, this function call from AI MoveToActor Function
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;
public:
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
	void MoveRight(float Throw);

	UFUNCTION(BlueprintCallable, category = Setup)
	void InitialTankTrack(class UTankTrackComponent* LeftTrackToSet, class UTankTrackComponent* RightTrackToSet);
	
};
