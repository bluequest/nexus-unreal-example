// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "ItemShopEntryUserWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * Widget used to display an item shop entry
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UItemShopEntryUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()
	
protected:

	void NativeConstruct() override;
	
	/** UTextBlock for containing the item's name */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ItemName;

	/** UTextBlock for containing the item's description */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ItemDescription;
	
	/** UButton for purchasing an item */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* PurchaseItemButton;

private:

	/** Callback for when the purchase item button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Item Shop Menu Buttons")
	void OnPurchaseItemButtonPressed();
};
