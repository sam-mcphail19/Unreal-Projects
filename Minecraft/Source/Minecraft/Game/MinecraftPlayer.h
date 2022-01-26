// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "MinecraftPlayer.generated.h"

UCLASS()
class MINECRAFT_API AMinecraftPlayer : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMinecraftPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MoveForce = 50000.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float JumpImpulse = 50.0f;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void LookUp(float Value);
	void LookRight(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);

	int32 JumpCount = 0;
	float VerticalVelocity = 0.0f;
};
