// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGenerator.h"

// Sets default values
AWorldGenerator::AWorldGenerator() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlockRegistry::Init();
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
	for (int i = -1; i < 5; i++) {
		for (int j = -1; j < 5; j++) {
			FVector Pos = FVector(i * AConstants::ChunkSize * AConstants::ChunkScale,
			                      j * AConstants::ChunkSize * AConstants::ChunkScale,
			                      0);
			AChunk* Chunk = GetWorld()->SpawnActor<AChunk>(
				Pos,
				FRotator(0, 0, 0)
			);
			Chunk->SetChunkOrigin(Pos);
		}
	}
}
