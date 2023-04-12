// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LinkAccountUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "Components/Button.h"

void ULinkAccountUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(BackButton))
	{
		BackButton->OnClicked.AddDynamic(this, &ULinkAccountUserWidget::OnBackButtonPressed);
	}
}

void ULinkAccountUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (IsValid(BackButton))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void ULinkAccountUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
	{
		RemoveFromParent();
		CharacterRef->LinkAccountWidget = nullptr;
	}
}
