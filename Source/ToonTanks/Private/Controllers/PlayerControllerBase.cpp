// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabledState(bool bEnable)
{
	if (bEnable)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}

	bShowMouseCursor = bEnable;
}