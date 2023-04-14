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

	if (IsValid(ReferralsBountiesButton))
	{
		ReferralsBountiesButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnReferralsBountiesButtonPressed);
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
	UCreatorSupportUserWidget* CreatorSupportWidget = CreateWidget<UCreatorSupportUserWidget>(GetWorld(), CreatorSupportWidgetClass);
	if (IsValid(CreatorSupportWidget))
	{
		CreatorSupportWidget->AddToViewport();

		if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
		{
			CharacterRef->CreatorSupportWidget = CreatorSupportWidget;
		}
	}
}

void UPauseMenuUserWidget::OnReferralsBountiesButtonPressed()
{
	ensure(IsValid(ReferralsBountiesMenuWidgetClass));
	UReferralsBountiesMenuUserWidget* ReferralsBountiesMenuWidget = CreateWidget<UReferralsBountiesMenuUserWidget>(GetWorld(), ReferralsBountiesMenuWidgetClass);
	if (IsValid(ReferralsBountiesMenuWidget))
	{
		ReferralsBountiesMenuWidget->AddToViewport();

		if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
		{
			CharacterRef->ReferralsBountiesMenuWidget = ReferralsBountiesMenuWidget;
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