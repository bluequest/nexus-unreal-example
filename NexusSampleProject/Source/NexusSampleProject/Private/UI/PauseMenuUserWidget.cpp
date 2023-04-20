// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "Components/Button.h"

void UPauseMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ASSIGN_ENSURE_REASON))
	{
		BackButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnBackButtonPressed);
	}

	if (ensureMsgf(IsValid(CreatorSupportButton), BP_ASSIGN_ENSURE_REASON))
	{
		CreatorSupportButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnCreatorSupportButtonPressed);
	}

	if (ensureMsgf(IsValid(ReferralsBountiesButton), BP_ASSIGN_ENSURE_REASON))
	{
		ReferralsBountiesButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnReferralsBountiesButtonPressed);
	}

	if (ensureMsgf(IsValid(ItemShopButton), BP_ASSIGN_ENSURE_REASON))
	{
		ItemShopButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnItemShopButtonPressed);
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
	ensureMsgf(IsValid(CreatorSupportWidgetClass), BP_ASSIGN_ENSURE_REASON);
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
	ensureMsgf(IsValid(ReferralsBountiesMenuWidgetClass), BP_ASSIGN_ENSURE_REASON);
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

void UPauseMenuUserWidget::OnItemShopButtonPressed()
{
	ensureMsgf(IsValid(ItemShopMenuWidgetClass), BP_ASSIGN_ENSURE_REASON);
	UItemShopMenuUserWidget* ItemShopMenuWidget = CreateWidget<UItemShopMenuUserWidget>(GetWorld(), ItemShopMenuWidgetClass);
	if (IsValid(ItemShopMenuWidget))
	{
		ItemShopMenuWidget->AddToViewport();

		if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
		{
			CharacterRef->ItemShopMenuWidget = ItemShopMenuWidget;
		}
	}
}

void UPauseMenuUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ASSIGN_ENSURE_REASON))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}