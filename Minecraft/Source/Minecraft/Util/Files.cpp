// Fill out your copyright notice in the Description page of Project Settings.

#include "Files.h"

UMaterial* Files::GetMaterial(FString Path) {
	Path = "Material'" + Path + "'";
	const ConstructorHelpers::FObjectFinder<UMaterial> Material(*Path);

	if (!Material.Succeeded()) {
		return nullptr;
	}

	return Material.Object;
}
