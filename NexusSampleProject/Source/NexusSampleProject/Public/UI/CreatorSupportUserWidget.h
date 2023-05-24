// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NexusPrototype.h"
#include "GameFramework/SaveGame.h"
#include "Generated/AttributionAPI.h"
#include "Generated/ReferralAPI.h"
#include "NexusShared.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "UI/LinkAccountUserWidget.h"
#include "CreatorSupportUserWidget.generated.h"

class UTextBlock;
class UButton;
class UEditableTextBox;
class UNexusSampleProjectSaveGame;

/**
 * Widget used to utilize Nexus Support-A-Creator functionality 
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UCreatorSupportUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public:
	void SetupInitialFocus(APlayerController* Controller) override;
	
	UPROPERTY(BlueprintReadOnly, Category = "Save Game")
	UNexusSampleProjectSaveGame* SaveGameInstance;

	UPROPERTY(BlueprintReadOnly, Category = "Creator Support Menu")
	TArray<FString> CreatorCodeList;

protected:

	void NativeConstruct() override;

	/** UButton for returning to game */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;

	/** UButton for submitting a referral code */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* SubmitButton;
	
	/** UEditableText for submitting a referral code */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* CreatorCodeInputTextBox;

	/** Int to set creator code character limit */
	UPROPERTY(EditAnywhere, Category = "Creator Support Menu")
	int32 CreatorCodeCharacterLimit = 6;

private:

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnBackButtonPressed();

	/** Callback for when the submit button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnSubmitButtonPressed();

	/** Callback for when CreatorCodeInputTextBox text changed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnTextChanged(const FText& Text);

	/** Callback for when saving the save game to slot completes */
	void OnAsyncSaveGameToSlotComplete(const FString& SlotName, const int32 UserIndex, bool bWasSuccessful);

	/** Callback for when loading the save game to slot completes */
	void OnAsyncLoadGameFromSlotComplete(const FString& SlotName, const int32 UserIndex, USaveGame* OutSaveGame);

	/** Callback for when GetCreatorsCompletes successfully */
	void OnGetCreatorsComplete(const FNexusAttributionGetCreators200Response& Response);

	/** Callback for when GetCreatorsCompletes fails */
	void OnGetCreatorsError(int32 ErrorCode);

	/** Callback for when OnGetReferralInfoByPlayerId completes, and returns a 200 response */
	void OnGetReferralInfoByPlayerId200ResponseComplete(const FNexusReferralGetReferralInfoByPlayerId200Response& Response);

	/** Callback for when OnGetReferralInfoByPlayerId completes, and returns a 400 response */
	void OnGetReferralInfoByPlayerId400ResponseComplete(const FNexusReferralReferralError& Response);

	/** Callback for when GetCreatorCodeCompletes fails */
	void OnGetReferralInfoByPlayerIdError(int32 ErrorCode);
};
