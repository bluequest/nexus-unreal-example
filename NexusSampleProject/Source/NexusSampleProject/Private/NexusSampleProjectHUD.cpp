// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusSampleProjectHUD.h"
#include "UI/HUDUserWidget.h"

void ANexusSampleProjectHUD::TogglePause()
{
	if (IsValid(PauseMenuWidget))
	{
		PauseMenuWidget->RemoveFromParent();
		PauseMenuWidget = nullptr;

		if (IsValid(CreatorSupportWidget))
		{
			CreatorSupportWidget->RemoveFromParent();
			CreatorSupportWidget = nullptr;
		}

		if (IsValid(LinkAccountWidget))
		{
			LinkAccountWidget->RemoveFromParent();
			LinkAccountWidget = nullptr;
		}

		if (IsValid(BountiesWidget))
		{
			BountiesWidget->RemoveFromParent();
			BountiesWidget = nullptr;
		}

		if (IsValid(ReferralsBountiesMenuWidget))
		{
			ReferralsBountiesMenuWidget->RemoveFromParent();
			ReferralsBountiesMenuWidget = nullptr;
		}

		if (IsValid(ItemShopMenuWidget))
		{
			ItemShopMenuWidget->RemoveFromParent();
			ItemShopMenuWidget = nullptr;
		}
	}
	else
	{
		ensure(IsValid(PauseMenuWidgetClass));
		PauseMenuWidget = CreateWidget<UPauseMenuUserWidget>(GetWorld(), PauseMenuWidgetClass);
		if (IsValid(PauseMenuWidget))
		{
			PauseMenuWidget->AddToViewport();
		}
	}
}

void ANexusSampleProjectHUD::BeginPlay()
{
	Super::BeginPlay();
	
	ensureMsgf(IsValid(HUDWidgetClass), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	HUDWidget = CreateWidget<UHUDUserWidget>(GetWorld(), HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}
