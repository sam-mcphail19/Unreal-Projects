// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Minecraft/Constants.h"
#include "Minecraft/Game/Block.h"
#include "Minecraft/Game/BlockRegistry.h"
#include "Minecraft/Game/Cube.h"
#include "Minecraft/Game/NoiseGenerator.h"
#include "Chunk.generated.h"

UCLASS()
class MINECRAFT_API AChunk : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChunk();

	UProceduralMeshComponent* Mesh;
	UMaterial* Material;

	enum EDirection {
		Forward,
		Right,
		Back,
		Left,
		Up,
		Down
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int Blocks[AConstants::ChunkSize * AConstants::ChunkSize * AConstants::WorldHeight];
	NoiseGenerator NoiseGen;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector ChunkOrigin;

	TArray<FVector> Vertices;
	TArray<int32> Indices;
	TArray<FVector> Normals;
	TArray<FLinearColor> Colors;
	TArray<FVector2D> UV0;

	int VertexCount = 0;

	void Populate();
	void CreateMesh();
	void ApplyMesh() const;
	void ClearMesh();
	void CreateQuad(EDirection Direction, FVector Pos);
	Block* GetBlock(FVector ChunkPos) const;
	void SetBlock(FVector ChunkPos, const Block* Block);
	void SetChunkOrigin(FVector Pos);

	static FVector IndexToPos(int Index);
	static int PosToIndex(FVector Pos);
	static FVector DirectionToVector(EDirection Direction);

	const FVector BlockVertexData[8] = {
			FVector(0, 0, 0),
			FVector(0, 0, 1),
			FVector(0, 1, 1),
			FVector(0, 1, 0),
			FVector(1, 1, 0),
			FVector(1, 1, 1),
			FVector(1, 0, 1),
			FVector(1, 0, 0)
		};


	const int BlockTriangleData[24] = {
			0, 1, 2, 3, // Forward
			3, 2, 5, 4, // Right
			4, 5, 6, 7, // Back
			7, 6, 1, 0, // Left
			1, 6, 5, 2, // Top
			7, 0, 3, 4 // Bottom
		};
};
