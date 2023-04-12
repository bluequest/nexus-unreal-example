// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "UI/LinkAccountUserWidget.h"
#include "CreatorSupportUserWidget.generated.h"

class UTextBlock;
class UButton;
class UEditableTextBox;
class UProgressBar;

/**
 * Widget used to utilize Nexus Support-A-Creator functionality 
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UCreatorSupportUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public:
	void SetupInitialFocus(APlayerController* Controller) override;

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<ULinkAccountUserWidget> LinkAccountWidgetClass;

protected:

	void NativeConstruct() override;

private:
	
	/** UTextBlock for containing the player's referral code */
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerReferralCode;

	/** UButton for returning to game */
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	/** UButton for submitting a referral code */
	UPROPERTY(meta = (BindWidget))
	UButton* SubmitButton;

	/** UButton for copying the player's referral code */
	UPROPERTY(meta = (BindWidget))
	UButton* CopyCodeButton;

	/** UButton for Nexus account linking information */
	UPROPERTY(meta = (BindWidget))
	UButton* LinkAccountButton;	
	
	/** UEditableText for submitting a referral code */
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CreatorCodeInputTextBox;

	/** UProgressBar the referral progress bar */
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ReferralProgressBar;

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnBackButtonPressed();

	/** Callback for when the submit button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnSubmitButtonPressed();

	/** Callback for when the copy button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnCopyButtonPressed();

	/** Callback for when the link account button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnLinkAccountButtonPressed();	
};
