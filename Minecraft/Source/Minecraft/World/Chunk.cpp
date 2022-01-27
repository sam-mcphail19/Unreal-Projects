// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

// Sets default values
AChunk::AChunk() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AChunk::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AChunk::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}


ABlock* AChunk::GetBlock(FVector ChunkPos) {
	return Blocks[PosToIndex(ChunkPos)];
}

void AChunk::SetBlock(FVector ChunkPos, ABlock* Block) {
	Blocks[PosToIndex(ChunkPos)] = Block;
}

void AChunk::SetChunkOrigin(FVector Pos) {
	ChunkOrigin = Pos;
}


// https://stackoverflow.com/questions/7367770/how-to-flatten-or-index-3d-array-in-1d-array
FVector AChunk::IndexToPos(int Index) {
	const int Z = Index / (AConstants::ChunkSize * AConstants::ChunkSize);
	Index -= Z * AConstants::ChunkSize * AConstants::ChunkSize;
	const int Y = Index / AConstants::ChunkSize;
	const int X = Index % AConstants::ChunkSize;

	return FVector(X, Y, Z);
}

int AChunk::PosToIndex(FVector Pos) {
	return Pos.Z * AConstants::ChunkSize * AConstants::ChunkSize + Pos.Y * AConstants::ChunkSize + Pos.X;
}
