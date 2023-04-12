// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "LinkAccountUserWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * Widget used to display information about how to link a user's nexus account with their referral code
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API ULinkAccountUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()


protected:

	void NativeConstruct() override;

public:

	void SetupInitialFocus(APlayerController* Controller) override;

	/** UButton for returning to game */
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

private:
	
	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Link Account Menu Buttons")
	void OnBackButtonPressed();

	/** UTextBlock for containing the player's referral code */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerReferralCode;
};
