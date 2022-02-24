// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	ArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	ArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(ArmComponent);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = GetPlayerController();

	if (playerController != nullptr) {
		playerController->Possess(this);
	}
}


APlayerController* ATank::GetPlayerController() {

	UWorld* world = GetWorld();
	APlayerController* playerController = nullptr;

	if (world != nullptr) {
		for (FConstPlayerControllerIterator Iterator = world->GetPlayerControllerIterator(); Iterator; ++Iterator) {
			playerController = Iterator->Get();
			break;
		}
	}

	return playerController;
}

void ATank::Move(float value)
{
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	float moveOffset = deltaTime * value * MoveSpeed;
	
	if (RootComponent) {
		RootComponent->AddLocalOffset(FVector(moveOffset, 0, 0), true);
	}
}

void ATank::Rotate(float value)
{
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	float moveOffset = deltaTime * value * RotateSpeed;

	if (TurretMesh) {
		TurretMesh->AddLocalRotation(FRotator(0, moveOffset, 0));
	}
}

void ATank::Turn(float value)
{
	float deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	float moveOffset = deltaTime * value * TurnSpeed;

	if (RootComponent) {
		RootComponent->AddLocalRotation(FRotator(0, moveOffset, 0), true);
	}
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::Rotate);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}


