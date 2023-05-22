// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NexusSampleProjectHUD.h"
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
	ensureMsgf(IsValid(PauseMenuWidgetClass), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	UPauseMenuUserWidget* PauseMenuWidgetRef = CreateWidget<UPauseMenuUserWidget>(GetWorld(), PauseMenuWidgetClass);
	if (IsValid(PauseMenuWidgetRef))
	{
		PauseMenuWidgetRef->AddToViewport();
		
		if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
		{
			HUD->PauseMenuWidget = PauseMenuWidgetRef;
		}
	}
}
