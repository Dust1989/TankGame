// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileActor.h"
#include "GameFrameWork/ProjectileMovementComponent.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileActor::LaunchProjectile(float Speed)
{
	if (ProjectileMovementComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire Speed: %f"), Speed);
		ProjectileMovementComp->SetActive(true);
		ProjectileMovementComp->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	}
	
}

