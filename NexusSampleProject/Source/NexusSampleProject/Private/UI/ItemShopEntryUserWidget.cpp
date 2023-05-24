// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemShopEntryUserWidget.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UItemShopEntryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(PurchaseItemButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		PurchaseItemButton->OnClicked.AddDynamic(this, &UItemShopEntryUserWidget::OnPurchaseItemButtonPressed);
	}
}

void UItemShopEntryUserWidget::OnPurchaseItemButtonPressed()
{
	// #NOTE: Just for this example project, we will just clear the item entry and display message that the item has been purchased.
	//
	// In a real project, shop/store integration should handle attributing the creator using the stored 
	// creator/referral code that was cached through UReferralsBountiesMenuUserWidget/UCreatorSupportUserWidget
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item Purchased, and attributed to creator!")));
	}

	UE_LOG(LogNexusSampleProject, Log, TEXT("Item Purchased, and attributed to creator!"));

	RemoveFromParent();
}