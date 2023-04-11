// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuUserWidget.h"
#include "Components/Button.h"

void UPauseMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPauseMenuUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (IsValid(BackButton))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}