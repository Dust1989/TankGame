// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
}


float ATank::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (DamageAmount > 0)
	{
		CurrentHealth = FMath::Clamp<float>(CurrentHealth - DamageAmount, 0, MaxHealth);
	}

	if (CurrentHealth <= 0)
	{
		OnDead.Broadcast();
	}

	return CurrentHealth;
}





