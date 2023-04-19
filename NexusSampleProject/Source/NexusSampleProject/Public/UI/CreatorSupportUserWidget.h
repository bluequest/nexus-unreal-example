// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NexusPrototype.h"
#include "GameFramework/SaveGame.h"
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

	/** #TODO Remove me when Unreal SDK is in. Delegate used for when retrieving cat facts completes */
	NexusSDK::FOnGetCatFactsComplete OnGetGatFactsCompleteDelegate;
	// #TODO ~End remove me

private:

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnBackButtonPressed();

	/** Callback for when the submit button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnSubmitButtonPressed();

	/** #TODO Remove me once Unreal SDK is in. NexusAPI - Callback for when Cat Facts are retrieved */
	void OnGetCatFactsComplete(const NexusSDK::FGetCatFactsResponse& Response);

	/** Callback for when saving the save game to slot completes */
	void OnAsyncSaveGameToSlotComplete(const FString& SlotName, const int32 UserIndex, bool bWasSuccessful);

	/** Callback for when loading the save game to slot completes */
	void OnAsyncLoadGameFromSlotComplete(const FString& SlotName, const int32 UserIndex, USaveGame* OutSaveGame);
};
