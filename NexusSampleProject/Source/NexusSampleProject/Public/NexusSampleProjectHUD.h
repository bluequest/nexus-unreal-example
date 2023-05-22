// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/PauseMenuUserWidget.h"
#include "UI/CreatorSupportUserWidget.h"
#include "UI/BountiesUserWidget.h"
#include "UI/ReferralsBountiesMenuUserWidget.h"
#include "NexusSampleProjectHUD.generated.h"

class UHUDUserWidget;

UCLASS()
class NEXUSSAMPLEPROJECT_API ANexusSampleProjectHUD : public AHUD
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Menus")
	void TogglePause();

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UHUDUserWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UHUDUserWidget* HUDWidget;

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UPauseMenuUserWidget> PauseMenuWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UPauseMenuUserWidget* PauseMenuWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UReferralsBountiesMenuUserWidget* ReferralsBountiesMenuWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UCreatorSupportUserWidget* CreatorSupportWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	ULinkAccountUserWidget* LinkAccountWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UBountiesUserWidget* BountiesWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UItemShopMenuUserWidget* ItemShopMenuWidget;

protected:
	void BeginPlay() override;	
};
