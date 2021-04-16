// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerController;
/**
 * 
 */
UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	APlayerController* PlayerControllerPtr;

	FVector MovementVecor;
	FQuat Rotation;
	bool bIsPlayerAlive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotationSpeed = 100.f;

	void CalculateMovementInput(float Value);
	void CalculateRotationInput(float Value);

	void Rotate();
	void Move();

public:
	// Sets default values for this pawn's properties
	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

	bool GetIsPlayerAlive() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
