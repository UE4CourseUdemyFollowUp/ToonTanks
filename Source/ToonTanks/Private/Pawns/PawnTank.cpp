// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/PawnTank.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

APawnTank::APawnTank()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);	
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Rotate();
	Move();

}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMovementInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotationInput);
}

void APawnTank::CalculateMovementInput(float Value)
{
	MovementVecor = FVector(Value * MovementSpeed * GetWorld()->DeltaTimeSeconds, 0.f, 0.f);
}

void APawnTank::CalculateRotationInput(float Value)
{
	FRotator RotationValue = FRotator(0.f, Value * RotationSpeed * GetWorld()->DeltaTimeSeconds, 0.f);
	Rotation = FQuat(RotationValue);
}

void APawnTank::Rotate()
{
	AddActorLocalOffset(MovementVecor, true);
}

void APawnTank::Move()
{
	AddActorLocalRotation(Rotation);
}
