// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/NexusSampleProjectBaseWidget.h"
#include "UI/PauseMenuUserWidget.h"
#include "HUDUserWidget.generated.h"

class UButton;

/**
 * Widget used for HUD
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UHUDUserWidget : public UNexusSampleProjectBaseWidget
{
	GENERATED_BODY()

public:

	void SetupInitialFocus(APlayerController* Controller) override;

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UPauseMenuUserWidget> PauseMenuWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UPauseMenuUserWidget* PauseMenuWidget;

protected:

	void NativeConstruct() override;

	/** UButton for pausing the game */
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* PauseButton;

private:

	/** Callback for when the pause button is pressed */
	UFUNCTION(BlueprintCallable, Category = "HUD Menu Buttons")
	void OnPauseButtonPressed();
};
