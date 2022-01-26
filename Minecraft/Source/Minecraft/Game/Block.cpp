// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

#include "Minecraft/World/WorldGenerator.h"

// Sets default values
ABlock::ABlock() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ABlock::BeginPlay() {
	Super::BeginPlay();

	const FTransform Transform = GetTransform();
	Mesh = GetWorld()->SpawnActor<ACube>(Transform.GetLocation(), Transform.Rotator());
	CreateCube(*Mesh, FLinearColor(255, 255, 255));
}

// Called every frame
void ABlock::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void ABlock::CreateCube(ACube& Cube, const FLinearColor& Color) {
	TArray<FVector> Vertices;
	TArray<int32> Indices;
	TArray<FLinearColor> Colors;

	for (int i = 0; i < ACube::NUM_VERTICES * 3; i += 3) {
		Vertices.Add(FVector(
			ACube::VERTEX_ARRAY[i] * AWorldGenerator::ChunkScale,
			ACube::VERTEX_ARRAY[i + 1] * AWorldGenerator::ChunkScale,
			ACube::VERTEX_ARRAY[i + 2] * AWorldGenerator::ChunkScale
		));
	}

	for (int i = 0; i < ACube::NUM_VERTICES; i += 4) {
		Indices.Add(i);
		Indices.Add(i + 1);
		Indices.Add(i + 2);

		Indices.Add(i + 2);
		Indices.Add(i + 3);
		Indices.Add(i);
	}

	int Index = 0;

	Cube.Mesh->SetMaterial(Index, UMaterialInstanceDynamic::Create(Cube.Material, Cube.Mesh));

	Cube.Mesh->CreateMeshSection_LinearColor(
		Index,
		Vertices,
		Indices,
		TArray<FVector>(),
		TArray<FVector2D>(),
		Colors,
		TArray<FProcMeshTangent>(),
		true
	);
}
