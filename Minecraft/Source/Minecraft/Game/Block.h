// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Minecraft/Util/Files.h"

class Block {
public:
	int Index;
	std::string Name;
	UMaterial* Material;

	Block(int Index, std::string Name, FString MaterialPath) {
		this->Index = Index;
		this->Name = Name;
		this->Material = Files::GetMaterial(MaterialPath);
	}

	Block(int Index, std::string Name) {
		this->Index = Index;
		this->Name = Name;
		this->Material = Files::GetMaterial("/Game/StarterContent/Materials/M_AssetPlatform.M_AssetPlatform");
	}
};
