// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorldBlocks.h"
#include "GameFramework/Actor.h"
#include "WorldGenerator.generated.h"

UCLASS()
class MINECRAFT_API AWorldGenerator : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWorldGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateWorld();
	void CreateBlock(int X, int Y, int Z);

	AWorldBlocks* World;

	static constexpr float ChunkScale = 100.0f;
};
