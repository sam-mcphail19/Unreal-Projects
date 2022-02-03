// Fill out your copyright notice in the Description page of Project Settings.


#include "BlockRegistry.h"

TMap<int, Block*> BlockRegistry::Blocks = TMap<int, Block*>();

void BlockRegistry::Init() {
	AddBlock(new Block(AIR, "Air"));
	AddBlock(new Block(DIRT, "Dirt", "/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass"));
}

void BlockRegistry::AddBlock(Block* NewBlock) {
	Blocks.Add(NewBlock->Index, NewBlock);
}

Block* BlockRegistry::GetBlock(int Index) {
	return *Blocks.Find(Index);
}
