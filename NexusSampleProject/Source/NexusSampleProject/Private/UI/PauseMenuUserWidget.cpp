// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuUserWidget.h"
#include "NexusSampleProjectHUD.h"
#include "Kismet/GameplayStatics.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "Components/Button.h"

void UPauseMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		BackButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnBackButtonPressed);
	}

	if (ensureMsgf(IsValid(CreatorSupportButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		CreatorSupportButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnCreatorSupportButtonPressed);
	}

	if (ensureMsgf(IsValid(ReferralsBountiesButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		ReferralsBountiesButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnReferralsBountiesButtonPressed);
	}

	if (ensureMsgf(IsValid(ItemShopButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		ItemShopButton->OnClicked.AddDynamic(this, &UPauseMenuUserWidget::OnItemShopButtonPressed);
	}
}

void UPauseMenuUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		RemoveFromParent();
		HUD->PauseMenuWidget = nullptr;
	}
}

void UPauseMenuUserWidget::OnCreatorSupportButtonPressed()
{
	ensureMsgf(IsValid(CreatorSupportWidgetClass), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	UCreatorSupportUserWidget* CreatorSupportWidget = CreateWidget<UCreatorSupportUserWidget>(GetWorld(), CreatorSupportWidgetClass);
	if (IsValid(CreatorSupportWidget))
	{
		CreatorSupportWidget->AddToViewport();

		if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
		{
			HUD->CreatorSupportWidget = CreatorSupportWidget;
		}
	}
}

void UPauseMenuUserWidget::OnReferralsBountiesButtonPressed()
{
	ensureMsgf(IsValid(ReferralsBountiesMenuWidgetClass), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	UReferralsBountiesMenuUserWidget* ReferralsBountiesMenuWidget = CreateWidget<UReferralsBountiesMenuUserWidget>(GetWorld(), ReferralsBountiesMenuWidgetClass);
	if (IsValid(ReferralsBountiesMenuWidget))
	{
		ReferralsBountiesMenuWidget->AddToViewport();

		if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
		{
			HUD->ReferralsBountiesMenuWidget = ReferralsBountiesMenuWidget;
		}
	}
}

void UPauseMenuUserWidget::OnItemShopButtonPressed()
{
	ensureMsgf(IsValid(ItemShopMenuWidgetClass), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	UItemShopMenuUserWidget* ItemShopMenuWidget = CreateWidget<UItemShopMenuUserWidget>(GetWorld(), ItemShopMenuWidgetClass);
	if (IsValid(ItemShopMenuWidget))
	{
		ItemShopMenuWidget->AddToViewport();

		if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
		{
			HUD->ItemShopMenuWidget = ItemShopMenuWidget;
		}
	}
}

void UPauseMenuUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}