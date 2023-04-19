// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "UI/ReferralsBountiesMenuUserWidget.h"
#include "UI/CreatorSupportUserWidget.h"
#include "UI/ItemShopMenuUserWidget.h"
#include "PauseMenuUserWidget.generated.h"

class UButton;

/**
 * Widget used for the pause menu
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UPauseMenuUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public:
	void SetupInitialFocus(APlayerController* Controller) override;

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UCreatorSupportUserWidget> CreatorSupportWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UReferralsBountiesMenuUserWidget> ReferralsBountiesMenuWidgetClass;
	
	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UItemShopMenuUserWidget> ItemShopMenuWidgetClass;

protected:

	void NativeConstruct() override;

	/** UButton for returning to game */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;

	/** UButton for Creator Support widget */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CreatorSupportButton;

	/** UButton for Referrals & Bounties widget */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ReferralsBountiesButton;

	/** UButton for Item Shop widget */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ItemShopButton;

private:

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Pause Menu Buttons")
	void OnBackButtonPressed();

	/** Callback for when the creator support button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Pause Menu Buttons")
	void OnCreatorSupportButtonPressed();

	/** Callback for when the referrals & bounties button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Pause Menu Buttons")
	void OnReferralsBountiesButtonPressed();

	/** Callback for when the item shop button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Pause Menu Buttons")
	void OnItemShopButtonPressed();
};
