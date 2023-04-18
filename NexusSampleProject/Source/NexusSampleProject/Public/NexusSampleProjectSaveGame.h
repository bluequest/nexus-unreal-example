// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NexusSampleProjectSaveGame.generated.h"

/**
 * Class used for save load. Primarily used for saving creator code for later use in transactions page
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UNexusSampleProjectSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	/** Field to save/load creator code */
	UPROPERTY(EditAnywhere, Category = "Data To Save")
	FString CreatorCode;

	/** Save slot name */
	UPROPERTY(EditAnywhere, Category = "Save Game ID Vars")
	FString SaveSlotName;

	/** User index value */
	UPROPERTY(EditAnywhere, Category = "Save Game ID Vars")
	int64 UserIndex;
};
