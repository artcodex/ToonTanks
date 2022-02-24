// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* ArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditInstanceOnly, Category="Movement")
	float MoveSpeed = 50.0f;

	UPROPERTY(EditInstanceOnly, Category = "Movement")
	float RotateSpeed = 50.0f;

	UPROPERTY(EditInstanceOnly, Category = "Movement")
	float TurnSpeed = 50.0f;
	
private:
	APlayerController* GetPlayerController();
	void Move(float value);
	void Rotate(float value);
	void Turn(float value);
};
