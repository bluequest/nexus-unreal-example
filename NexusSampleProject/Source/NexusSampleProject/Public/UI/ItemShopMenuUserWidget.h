// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "ItemShopMenuUserWidget.generated.h"

class UButton;
class UTextBlock;
class UNexusSampleProjectSaveGame;

/**
 * Widget used for the item shop (purchasing menu)
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UItemShopMenuUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public:
	
	void SetupInitialFocus(APlayerController* Controller) override;

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Nexus API")
	void UpdateCreatorCodeDisplay();

protected:

	void NativeConstruct() override;

	/** UButton for returning to game */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;

	/** UTextBlock for displaying current creator code */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CreatorCodeTextBox;

private:

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Item shop buttons")
	void OnBackButtonPressed();

	/** Callback for when loading the save game from slot completes */
	void OnAsyncLoadGameFromSlotComplete(const FString& SlotName, const int32 UserIndex, USaveGame* OutSaveGame);
};
