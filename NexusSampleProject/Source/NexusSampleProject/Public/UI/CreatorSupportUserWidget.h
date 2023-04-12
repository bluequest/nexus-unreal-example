// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "CreatorSupportUserWidget.generated.h"

class UButton;
class UEditableTextBox;

/**
 * Widget used to utilize Nexus Support-A-Creator functionality 
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UCreatorSupportUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public:
	void SetupInitialFocus(APlayerController* Controller) override;

protected:

	void NativeConstruct() override;

private:
	/** UButton for returning to game */
	UPROPERTY(meta = (BindWidget))
	UButton* BackButton;

	/** UButton for submitting a creator code */
	UPROPERTY(meta = (BindWidget))
	UButton* SubmitButton;

	/** UEditableText for submitting a creator code */
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CreatorCodeInputTextBox;

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnBackButtonPressed();

	/** Callback for when the submit button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Creator Support Menu Buttons")
	void OnSubmitButtonPressed();
};
