// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BountiesEntryUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UBountiesEntryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(CollectBountyButton), BP_ASSIGN_ENSURE_REASON))
	{
		CollectBountyButton->OnClicked.AddDynamic(this, &UBountiesEntryUserWidget::OnCollectBountyButtonPressed);
	}
}

void UBountiesEntryUserWidget::OnCollectBountyButtonPressed()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Bounty Collected!")));
	}

	RemoveFromParent();
}