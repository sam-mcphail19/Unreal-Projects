// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Block.h"

class MINECRAFT_API BlockRegistry {
public:
	static TMap<int, Block*> Blocks;

	static void Init();
	static void AddBlock(Block* NewBlock);
	static Block* GetBlock(int Index);
};

enum BLOCKS {
	AIR,
	DIRT,
};
