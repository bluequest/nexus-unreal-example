// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusSampleProjectHUD.h"
#include "UI/HUDUserWidget.h"

void ANexusSampleProjectHUD::BeginPlay()
{
	Super::BeginPlay();
	
	ensureMsgf(IsValid(HUDWidgetClass), BP_ASSIGN_ENSURE_REASON);
	HUDWidget = CreateWidget<UHUDUserWidget>(GetWorld(), HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}
