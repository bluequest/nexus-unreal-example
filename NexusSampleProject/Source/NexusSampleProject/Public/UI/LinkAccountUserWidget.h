// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "NexusShared.h"
#include "Generated/AttributionAPI.h"
#include "Generated/ReferralAPI.h"
#include "LinkAccountUserWidget.generated.h"

class UButton;
class UTextBlock;
class UNexusSampleProjectSaveGame;

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

	UPROPERTY(BlueprintReadOnly, Category = "Save Game")
	UNexusSampleProjectSaveGame* SaveGameInstance;

public:

	void SetupInitialFocus(APlayerController* Controller) override;

	UFUNCTION(BlueprintCallable, Category = "Nexus API")
	void UpdatePlayerReferralCode();

private:
	
	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Link Account Menu Buttons")
	void OnBackButtonPressed();

	/** Callback for when loading the save game to slot completes */
	void OnAsyncLoadGameFromSlotComplete(const FString& SlotName, const int32 UserIndex, USaveGame* OutSaveGame);

	/** Callback for when GetCreatorsCompletes successfully */
	void OnGetCreatorsComplete(const FNexusAttributionGetCreators200Response& Response);

	/** Callback for when GetCreatorsCompletes fails */
	void OnGetCreatorsError(int32 ErrorCode);

	/** Callback for when OnGetReferralInfoByPlayerId completes for the 1st player in the GetCreators call, and returns a 200 response */
	void OnGetReferralInfoByPlayerIdFirstCreator200ResponseComplete(const FNexusReferralGetReferralInfoByPlayerId200Response& Response);

	/** Callback for when OnGetReferralInfoByPlayerId completes, and returns a 400 response */
	void OnGetReferralInfoByPlayerId400ResponseComplete(const FNexusReferralReferralError& Response);

	/** Callback for when GetCreatorCodeCompletes fails */
	void OnGetReferralInfoByPlayerIdError(int32 ErrorCode);
};
