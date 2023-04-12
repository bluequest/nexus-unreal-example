// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NexusSampleProjectBaseWidget.h"

void UNexusSampleProjectBaseWidget::SetupInitialFocus(APlayerController* Controller)
{
}

void UNexusSampleProjectBaseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetupInitialFocus(GetOwningPlayer());
}
