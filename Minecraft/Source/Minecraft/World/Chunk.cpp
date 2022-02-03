// Fill out your copyright notice in the Description page of Project Settings.


#include "Chunk.h"

// Sets default values
AChunk::AChunk() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>("CustomMesh");
	Material = CreateDefaultSubobject<UMaterial>("DefaultMaterial");

	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void AChunk::BeginPlay() {
	Super::BeginPlay();

	Populate();
	CreateMesh();
	ApplyMesh();
}

// Called every frame
void AChunk::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AChunk::Populate() {
	for (int i = 0; i < AConstants::ChunkSize * AConstants::ChunkSize; i++) {
		const FVector BlockPos = IndexToPos(i);
		SetBlock(BlockPos, BlockRegistry::GetBlock(DIRT));
	}
}

void AChunk::CreateMesh() {
	for (int i = 0; i < AConstants::ChunkSize * AConstants::ChunkSize * AConstants::WorldHeight; i++) {
		if (Blocks[i] == AIR)
			continue;

		for (int j = 0; j < 6; j++) {
			CreateQuad(static_cast<EDirection>(j), IndexToPos(i) + ChunkOrigin);
		}
		// For some reason if this is not created again after, then the face is missing
		CreateQuad(Forward, IndexToPos(i) + ChunkOrigin);
	}
}


void AChunk::ApplyMesh() const {
	Mesh->SetMaterial(0, Material);

	Mesh->CreateMeshSection_LinearColor(
		0,
		Vertices,
		Indices,
		Normals,
		UV0,
		Colors,
		TArray<FProcMeshTangent>(),
		true
	);
}

void AChunk::ClearMesh() {
	Vertices.Empty();
	Indices.Empty();
	Normals.Empty();
	UV0.Empty();
	Colors.Empty();

	VertexCount = 0;
}

void AChunk::CreateQuad(EDirection Direction, FVector Pos) {
	for (int i = 0; i < 4; i++) {
		Vertices.Add(
			(BlockVertexData[BlockTriangleData[i + static_cast<int>(Direction) * 4]] + Pos) *
			AConstants::ChunkScale
		);
	}

	VertexCount += 4;

	Indices.Append({VertexCount + 3, VertexCount + 2, VertexCount, VertexCount + 2, VertexCount + 1, VertexCount});

	FVector Normal = DirectionToVector(Direction);
	Normals.Append({Normal, Normal, Normal, Normal});

	FLinearColor Color = FLinearColor::Green;
	Colors.Append({Color, Color, Color, Color});

	UV0.Append({FVector2D(1, 1), FVector2D(1, 0), FVector2D(0, 0), FVector2D(0, 1)});
}


Block* AChunk::GetBlock(const FVector ChunkPos) const {
	return BlockRegistry::GetBlock(Blocks[PosToIndex(ChunkPos)]);
}

void AChunk::SetBlock(const FVector ChunkPos, const Block* Block) {
	Blocks[PosToIndex(ChunkPos)] = Block->Index;
}

void AChunk::SetChunkOrigin(const FVector Pos) {
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

int AChunk::PosToIndex(const FVector Pos) {
	return Pos.Z * AConstants::ChunkSize * AConstants::ChunkSize + Pos.Y * AConstants::ChunkSize + Pos.X;
}

FVector AChunk::DirectionToVector(EDirection Direction) {
	switch (Direction) {
	case Forward: return FVector::ForwardVector;
	case Right: return FVector::RightVector;
	case Back: return FVector::BackwardVector;
	case Left: return FVector::LeftVector;
	case Up: return FVector::UpVector;
	case Down: return FVector::DownVector;
	default: throw std::invalid_argument("Invalid direction");
	}
}
