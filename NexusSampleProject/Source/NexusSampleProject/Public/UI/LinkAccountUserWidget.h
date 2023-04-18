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

	/** UButton for returning to game */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;

	/** UTextBlock for containing the player's referral code */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* PlayerReferralCode;

	/** #TODO Remove me when Unreal SDK template is in. Delegate used for when retrieving player's referral code completes */
	//NexusSDK::FOnGetReferralCodeComplete OnGetReferralCodeCompleteDelegate;

public:

	void SetupInitialFocus(APlayerController* Controller) override;

	UFUNCTION(BlueprintCallable, Category = "Nexus API")
	void UpdatePlayerReferralCode();

private:
	
	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Link Account Menu Buttons")
	void OnBackButtonPressed();

	/** NexusAPI - Callback for when retrieving the player's referral code completes */
	void OnGetPlayerReferralCodeComplete(FString& ReferralCode, bool bWasSuccessful);
};
