// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "Engine/Texture2DDynamic.h"
#include "BountiesEntryUserWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;
class UProgressBar;

/**
 * Widget entry to display information about a referral bounty
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UBountiesEntryUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public: 
	
	UFUNCTION(BlueprintCallable)
	void SetBountyDescription(FString InDescription);

	UFUNCTION(BlueprintCallable)
	void SetBountyImage(FString InURL);

	UFUNCTION(BlueprintCallable)
	void SetBountyTitle(FString InTitle);

protected:

	void NativeConstruct() override;

	/** UProgressBar for tracking the bounty's progress */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UProgressBar* BountyProgressBar;
	
	/** UTextBlock for containing the bounty's title */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* BountyTitle;

	/** UTextBlock for containing the bounty's description */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* BountyDescription;
	
	/** UButton for collecting a referral bounty */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CollectBountyButton;

	/** UImage for collecting a referral bounty */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UImage* BountyImage;

private:

	/** Callback for when the collect bounty button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Bounties Menu Buttons")
	void OnCollectBountyButtonPressed();

	/** Callback for downloading texture from url completes */
	UFUNCTION()
	void OnGetTexture2D(UTexture2DDynamic* _texture);
};