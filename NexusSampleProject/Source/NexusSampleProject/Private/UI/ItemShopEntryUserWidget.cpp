// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemShopEntryUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UItemShopEntryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensure(IsValid(PurchaseItemButton)))
	{
		PurchaseItemButton->OnClicked.AddDynamic(this, &UItemShopEntryUserWidget::OnPurchaseItemButtonPressed);
	}
}

void UItemShopEntryUserWidget::OnPurchaseItemButtonPressed()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item Purchased!")));
	}

	RemoveFromParent();
}
