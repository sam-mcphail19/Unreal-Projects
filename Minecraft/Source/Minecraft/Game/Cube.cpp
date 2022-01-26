// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"

#include "Minecraft/Util/Files.h"

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