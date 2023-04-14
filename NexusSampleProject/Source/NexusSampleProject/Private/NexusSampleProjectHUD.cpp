// Fill out your copyright notice in the Description page of Project Settings.


#include "NexusSampleProjectHUD.h"
#include "UI/HUDUserWidget.h"

void ANexusSampleProjectHUD::BeginPlay()
{
	Super::BeginPlay();
	
	ensure(IsValid(HUDWidgetClass));
	HUDWidget = CreateWidget<UHUDUserWidget>(GetWorld(), HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}
