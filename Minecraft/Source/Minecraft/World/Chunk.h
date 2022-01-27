// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Minecraft/Game/Block.h"
#include "Minecraft/Constants.h"
#include "Chunk.generated.h"

UCLASS()
class MINECRAFT_API AChunk : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChunk();

	ABlock* GetBlock(FVector ChunkPos);
	void SetBlock(FVector ChunkPos, ABlock* Block);
	FVector ChunkOrigin;
	void SetChunkOrigin(FVector Pos);

	static FVector IndexToPos(int Index);
	static int PosToIndex(FVector Pos);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	ABlock* Blocks[AConstants::ChunkSize * AConstants::ChunkSize * AConstants::WorldHeight];

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
