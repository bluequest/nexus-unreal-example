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
	// #TODO Replace logic when Unreal SDK template is in.
	//OnCreateNewSaleTransactionCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnCreateNewSaleTransactionComplete);
	//NexusSDK::CreateNewSaleTransaction(FString GroupId, OnCreateNewSaleTransactionCompleteDelegate);
	OnCreateNewSaleTransactionComplete(true);
}

void UItemShopEntryUserWidget::OnCreateNewSaleTransactionComplete(/* FTransactionStruct TransactionInfo, */ bool bWasSuccessful)
{
	if (bWasSuccessful) 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Item Purchased, and attributed to creator!")));
		}

		UE_LOG(LogNexusSampleProject, Log, TEXT("Item Purchased, and attributed to creator!"));

		RemoveFromParent();
	}
	else 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Failed to purchase item, and attribute to creator!")));
		}

		UE_LOG(LogNexusSampleProject, Error, TEXT("Failed to purchase item, and attribute to creator!"));
	}
}
