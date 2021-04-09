// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/PawnBase.h"
#include <Components/CapsuleComponent.h>
#include <Components/SceneComponent.h>
#include "Actors/ProjectileBase.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

}

void APawnBase::RotateTurretAt(FVector LookAtTarget)
{
	FVector TargetLocation = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);

	FRotator LookAtRotation = (TargetLocation - TurretMesh->GetComponentLocation()).Rotation();

	TurretMesh->SetWorldRotation(LookAtRotation);
}

void APawnBase::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("APawnBase::Fire()"));

	if (ProjectileClass)
	{
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
		AProjectileBase* Projectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, Location, Rotation);
		Projectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	UE_LOG(LogTemp, Warning, TEXT("APawnBase::HandleDestruction()"));
}

