// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"

// Sets default values
ACube::ACube() : Mesh(CreateDefaultSubobject<UProceduralMeshComponent>("CustomMesh")) {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetRootComponent(Mesh);

	Material = Files::GetMaterial("/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass");
}

// Called when the game starts or when spawned
void ACube::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ACube::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

const int ACube::VERTEX_ARRAY[NUM_VERTICES * 3] = {
		// Bottom
		0, 0, 0,
		1, 0, 0,
		1, 1, 0,
		0, 1, 0,

		// Top
		1, 0, 1,
		0, 0, 1,
		0, 1, 1,
		1, 1, 1,

		// Left
		0, 0, 1,
		0, 0, 0,
		0, 1, 0,
		0, 1, 1,

		// Right
		1, 0, 0,
		1, 0, 1,
		1, 1, 1,
		1, 1, 0,

		// Front
		1, 0, 0,
		0, 0, 0,
		0, 0, 1,
		1, 0, 1,

		// Back
		0, 1, 0,
		1, 1, 0,
		1, 1, 1,
		0, 1, 1
	};

void ACube::CreateCube() {
	for (int i = 0; i < NUM_VERTICES * 3; i += 3) {
		Vertices.Add(FVector(
			VERTEX_ARRAY[i] * AConstants::ChunkScale,
			VERTEX_ARRAY[i + 1] * AConstants::ChunkScale,
			VERTEX_ARRAY[i + 2] * AConstants::ChunkScale
		));
	}

	for (int i = 0; i < NUM_VERTICES; i += 4) {
		Indices.Add(i);
		Indices.Add(i + 1);
		Indices.Add(i + 2);

		Indices.Add(i + 2);
		Indices.Add(i + 3);
		Indices.Add(i);
	}

	int Index = 0;

	Mesh->SetMaterial(Index, UMaterialInstanceDynamic::Create(Material, Mesh));

	Mesh->CreateMeshSection_LinearColor(
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
