// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileActor.h"
#include "GameFrameWork/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	ProjectileMovementComp->bAutoActivate = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComp);
	MeshComp->SetNotifyRigidBodyCollision(true);

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticle"));
	TrailParticle->SetupAttachment(MeshComp);

	ExplodeParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplodePartilcle"));
	ExplodeParticle->SetupAttachment(MeshComp);
	ExplodeParticle->bAutoActivate = false;

	ExplodeForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("ExplodeForce"));
	ExplodeForce->SetupAttachment(MeshComp);
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	MeshComp->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);
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
		ProjectileMovementComp->SetActive(true);
		ProjectileMovementComp->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	}
	
}

void AProjectileActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit...."));
	TrailParticle->Deactivate();
	ExplodeParticle->Activate();

	ExplodeForce->FireImpulse();

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetVisibility(false);
	//SetLifeSpan(5);
	GetWorldTimerManager().SetTimer(Destroy_TimerHandle, this, &AProjectileActor::DestroyProjectile, DestroyDelay);

	UGameplayStatics::ApplyRadialDamage(this, DamageAmount, GetActorLocation(), ExplodeForce->Radius, UDamageType::StaticClass(), TArray<AActor*>());
}

void AProjectileActor::DestroyProjectile()
{
	Destroy();
}
