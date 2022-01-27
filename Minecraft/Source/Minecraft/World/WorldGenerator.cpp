// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGenerator.h"

// Sets default values
AWorldGenerator::AWorldGenerator() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWorldGenerator::BeginPlay() {
	Super::BeginPlay();

	GenerateWorld();
}

// Called every frame
void AWorldGenerator::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AWorldGenerator::GenerateWorld() {
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			CreateChunk(FVector(i, j, 0));
		}
	}
}

ABlock* AWorldGenerator::CreateBlock(FVector Pos) {
	return CreateBlock(Pos.X, Pos.Y, Pos.Z);
}

ABlock* AWorldGenerator::CreateBlock(int X, int Y, int Z) {
	ABlock* Block = GetWorld()->SpawnActor<ABlock>(
		FVector(X * AConstants::ChunkScale, Y * AConstants::ChunkScale, Z),
		FRotator(0, 0, 0)
	);
	return Block;
}

AChunk* AWorldGenerator::CreateChunk(FVector Pos) {
	AChunk* Chunk = GetWorld()->SpawnActor<AChunk>(
		Pos,
		FRotator(0, 0, 0)
	);

	// All blocks under a height of 16
	for (int i = 0; i < 16 * AConstants::ChunkSize * AConstants::ChunkSize; i++) {
		const FVector BlockPos = AChunk::IndexToPos(i);
		Chunk->SetBlock(BlockPos, CreateBlock(BlockPos + Chunk->ChunkOrigin));
	}

	return Chunk;
}
