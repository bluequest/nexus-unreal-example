// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "Components/Button.h"

void UHUDUserWidget::NativeConstruct()
{
	if (IsValid(PauseButton))
	{
		PauseButton->OnClicked.AddDynamic(this, &UHUDUserWidget::OnPauseButtonPressed);
	}
}

void UHUDUserWidget::OnPauseButtonPressed()
{
	ensure(IsValid(PauseMenuWidgetClass));
	UPauseMenuUserWidget* PauseMenuWidgetRef = CreateWidget<UPauseMenuUserWidget>(GetWorld(), PauseMenuWidgetClass);
	if (IsValid(PauseMenuWidgetRef))
	{
		PauseMenuWidgetRef->AddToViewport();
		if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
		{
			CharacterRef->PauseMenuWidget = PauseMenuWidgetRef;
		}
	}
}
