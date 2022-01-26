// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldGenerator.h"

#include "WorldBlocks.h"
#include "Kismet/GameplayStatics.h"
#include "Minecraft/Game/Block.h"

// Sets default values
AWorldGenerator::AWorldGenerator() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWorldGenerator::BeginPlay() {
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldBlocks::StaticClass(), FoundActors);
	World = static_cast<AWorldBlocks*>(FoundActors[0]);

	GenerateWorld();
}

// Called every frame
void AWorldGenerator::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AWorldGenerator::GenerateWorld() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			CreateBlock(i, j, 0);
		}
	}
}

void AWorldGenerator::CreateBlock(int X, int Y, int Z) {
	ABlock* Block = GetWorld()->SpawnActor<ABlock>(
		FVector(X * ChunkScale, Y * ChunkScale, Z),
		FRotator(0, 0, 0)
	);
}
