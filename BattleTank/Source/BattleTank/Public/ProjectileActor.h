// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

UCLASS()
class BATTLETANK_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UParticleSystemComponent* TrailParticle;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UParticleSystemComponent* ExplodeParticle;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class URadialForceComponent* ExplodeForce;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	float DestroyDelay = 5;

	UPROPERTY(EditDefaultsOnly, Category = "SetUp")
	float DamageAmount = 100;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = Fire)
	void LaunchProjectile(float Speed);
	
private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	FTimerHandle Destroy_TimerHandle;

	void DestroyProjectile();
};
