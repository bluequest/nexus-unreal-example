// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "BountiesEntryUserWidget.generated.h"

class UButton;
class UTextBlock;
class UProgressBar;

/**
 * Widget entry to display information about a referral bounty
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UBountiesEntryUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

protected:

	void NativeConstruct() override;

private:

	/** UProgressBar for tracking the bounty's progress */
	UPROPERTY(meta = (BindWidget))
	UProgressBar* BountyProgressBar;
	
	/** UTextBlock for containing the bounty's title */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BountyTitle;

	/** UTextBlock for containing the bounty's description */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BountyDescription;
	
	/** UButton for collecting a referral bounty */
	UPROPERTY(meta = (BindWidget))
	UButton* CollectBountyButton;

	/** Callback for when the collect bounty button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Bounties Menu Buttons")
	void OnCollectBountyButtonPressed();
};