// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "Components/Button.h"

void UPauseMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(BackButton))
	{
		BackButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnBackButtonPressed);
	}

	if (IsValid(CreatorSupportButton))
	{
		CreatorSupportButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnCreatorSupportButtonPressed);
	}
}

void UPauseMenuUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
	{
		RemoveFromParent();
		CharacterRef->PauseMenuWidget = nullptr;
	}
}

void UPauseMenuUserWidget::OnCreatorSupportButtonPressed()
{
	ensure(IsValid(CreatorSupportWidgetClass));
	CreatorSupportWidget = CreateWidget<UCreatorSupportUserWidget>(GetWorld(), CreatorSupportWidgetClass);
	if (IsValid(CreatorSupportWidget))
	{
		CreatorSupportWidget->AddToViewport();

		if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
		{
			CharacterRef->CreatorSupportWidget = CreatorSupportWidget;
		}
	}
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