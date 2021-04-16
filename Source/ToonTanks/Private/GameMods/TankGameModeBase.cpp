// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMods/TankGameModeBase.h"
#include "Pawns/PawnTank.h"
#include "Pawns/PawnTurret.h"
#include "Controllers/PlayerControllerBase.h"
#include "Kismet/GameplayStatics.h"

void ATankGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void ATankGameModeBase::HandleGameStart()
{
	TurretsAlive = GetCurrentTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();
	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}
}

void ATankGameModeBase::HandleGameOver(bool IsWin)
{
	GameOver(IsWin);
}

int32 ATankGameModeBase::GetCurrentTurretCount() const
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), Turrets);
	return Turrets.Num();
}

void ATankGameModeBase::ActorDied(AActor* Actor)
{
	if (Actor == PlayerTank)
	{
		PlayerTank->HandleDestruction();

		HandleGameOver(false);
		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DeadTurret = Cast<APawnTurret>(Actor))
	{
		DeadTurret->HandleDestruction();	

		if (--TurretsAlive <= 0)
		{
			HandleGameOver(true);
		}
	}
}

