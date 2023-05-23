// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "UI/LinkAccountUserWidget.h"
#include "Generated/AttributionAPI.h"
#include "Generated/ReferralAPI.h"
#include "NexusShared.h"
#include "ReferralsBountiesMenuUserWidget.generated.h"

class UTextBlock;
class UButton;
class UEditableTextBox;
class UProgressBar;
class UBountiesUserWidget;
class UNexusSampleProjectSaveGame;

/**
 * Widget used to utilize Nexus Referrals & Bounties functionality
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UReferralsBountiesMenuUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public:
	void SetupInitialFocus(APlayerController* Controller) override;

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<ULinkAccountUserWidget> LinkAccountWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UBountiesUserWidget> BountiesWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Save Game")
	UNexusSampleProjectSaveGame* SaveGameInstance;
	
	UPROPERTY(BlueprintReadOnly, Category = "Referrals & Bounties Menu")
	TArray<FString> ReferralCodeList;

	UPROPERTY(BlueprintReadOnly, Category = "Referrals & Bounties Menu")
	FString LocalPlayerReferralCode;

	UFUNCTION(BlueprintCallable, Category = "Nexus API")
	void UpdatePlayerReferralCode();

	UFUNCTION(BlueprintCallable, Category = "Nexus API")
	void UpdateSavedReferralCode();

protected:

	void NativeConstruct() override;

	/** UTextBlock for containing the player's referral code */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* PlayerReferralCode;

	/** UButton for returning to game */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;

	/** UButton for submitting a referral code */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SubmitButton;

	/** UButton for copying the player's referral code */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CopyCodeButton;

	/** UButton for viewing the player's referral bounties */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ViewBoutniesButton;
	
	/** UButton for Nexus account linking information */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* LinkAccountButton;	
	
	/** UEditableText for submitting a referral code */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* ReferralCodeInputTextBox;

	/** UProgressBar the referral progress bar */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* ReferralProgressBar;

private:
	
	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Referrals & Bounties Menu Buttons")
	void OnBackButtonPressed();

	/** Callback for when the submit button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Referrals & Bounties Menu Buttons")
	void OnSubmitButtonPressed();

	/** Callback for when the copy button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Referrals & Bounties Menu Buttons")
	void OnCopyButtonPressed();

	/** Callback for when the link account button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Referrals & Bounties Menu Buttons")
	void OnLinkAccountButtonPressed();	

	/** Callback for when the view bounties button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Referrals & Bounties Menu Buttons")
	void OnViewBountiesButtonPressed();	

	/** Callback for when GetCreatorsCompletes successfully */
	void OnGetCreatorsComplete(const FNexusAttributionGetCreators200Response& Response);

	/** Callback for when GetCreatorsCompletes fails */
	void OnGetCreatorsError(int32 ErrorCode);

	/** Callback for when OnGetReferralInfoByPlayerId completes for the 1st player in the GetCreators call, and returns a 200 response */
	void OnGetReferralInfoByPlayerIdFirstCreator200ResponseComplete(const FNexusReferralGetReferralInfoByPlayerId200Response& Response);

	/** Callback for when OnGetReferralInfoByPlayerId completes, and returns a 200 response */
	void OnGetReferralInfoByPlayerId200ResponseComplete(const FNexusReferralGetReferralInfoByPlayerId200Response& Response);

	/** Callback for when OnGetReferralInfoByPlayerId completes, and returns a 400 response */
	void OnGetReferralInfoByPlayerId400ResponseComplete(const FNexusReferralReferralError& Response);

	/** Callback for when GetCreatorCodeCompletes fails */
	void OnGetReferralInfoByPlayerIdError(int32 ErrorCode);

	/** Callback for when saving the save game to slot completes */
	void OnAsyncSaveGameToSlotComplete(const FString& SlotName, const int32 UserIndex, bool bWasSuccessful);

	/** Callback for when loading the save game to slot completes */
	void OnAsyncLoadGameFromSlotComplete(const FString& SlotName, const int32 UserIndex, USaveGame* OutSaveGame);
};