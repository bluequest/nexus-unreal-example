// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "UI/ReferralsBountiesMenuUserWidget.h"
#include "UI/CreatorSupportUserWidget.h"
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

protected:

	void NativeConstruct() override;

private:

	/** UButton for returning to game */
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	/** UButton for Creator Support widget */
	UPROPERTY(meta = (BindWidget))
	UButton* CreatorSupportButton;

	/** UButton for Referrals & Bounties widget */
	UPROPERTY(meta = (BindWidget))
	UButton* ReferralsBountiesButton;

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Pause Menu Buttons")
	void OnBackButtonPressed();

	/** Callback for when the creator support button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Pause Menu Buttons")
	void OnCreatorSupportButtonPressed();

	/** Callback for when the referrals & bounties button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Pause Menu Buttons")
	void OnReferralsBountiesButtonPressed();
};
