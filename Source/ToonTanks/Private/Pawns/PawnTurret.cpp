// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/PawnTurret.h"
#include <Kismet/Gameplaystatics.h>
#include "Pawns/PawnTank.h"

APawnTurret::APawnTurret()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APawnTurret::CheckFireCondition()
{
	if (!PlayerPawn)
		return;

	if (GetDistanceToPlayer() <= FireRange)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fire"));
	}	
}

float APawnTurret::GetDistanceToPlayer()
{
	if (!PlayerPawn)
		return 0.f;

	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}