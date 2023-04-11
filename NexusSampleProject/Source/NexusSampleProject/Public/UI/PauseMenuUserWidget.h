// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "PauseMenuUserWidget.generated.h"

class UButton;

/**
 * Widget used for the pause menu
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UPauseMenuUserWidget : public UNexusSampleProjectBaseWidget
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

	/** UButton for Creator Support widget */
	UPROPERTY(meta = (BindWidget))
	UButton* CreatorSupportButton;
};
