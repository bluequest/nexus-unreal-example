// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "UI/BountiesEntryUserWidget.h"
#include "Generated/BountyAPI.h"
#include "NexusShared.h"
#include "BountiesUserWidget.generated.h"

class UButton;
class UScrollBox;

/**
 * Widget used to display a list of player's referral bounties
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UBountiesUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public:
	void SetupInitialFocus(APlayerController* Controller) override;

protected:

	void NativeConstruct() override;

	/** UButton for returning to game */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* BackButton;

	/** UScrollBox for containing referral bounties */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UScrollBox* BountiesReferralScrollBox;

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UBountiesEntryUserWidget> BountiesEntryWidgetClass;

private:

	/** Callback for when the back button is pressed */
	UFUNCTION(BlueprintCallable, Category = "Bounties Menu Buttons")
	void OnBackButtonPressed();

	/** Callback for when GetBounties completes and returns a 200 response */
	void OnGetBounties200ResponseComplete(const FNexusBountyGetBounties200Response& Response);

	/** Callback for when GetBounties completes and returns a 400 response */
	void OnGetBounties400ResponseComplete(const FNexusBountyBountyError& Response);

	/** Callback for when GetBounties fails */
	void OnGetBountiesError(int32 ErrorCode);
};
