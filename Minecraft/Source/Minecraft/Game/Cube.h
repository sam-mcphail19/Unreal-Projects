// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Minecraft/Constants.h"
#include "Minecraft/Util/Files.h"
#include "Cube.generated.h"

UCLASS()
class MINECRAFT_API ACube : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACube();

	UPROPERTY()
	UProceduralMeshComponent* Mesh;

	UMaterial* Material;

	TArray<FVector> Vertices;
	TArray<int32> Indices;
	TArray<FLinearColor> Colors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void CreateCube();

	const static int NUM_VERTICES = 6 * 4;
	const static int VERTEX_ARRAY[NUM_VERTICES * 3];
};
