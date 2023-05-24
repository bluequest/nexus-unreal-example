// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BountiesEntryUserWidget.h"
#include "Blueprint/AsyncTaskDownloadImage.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UBountiesEntryUserWidget::SetBountyDescription(FString InDescription)
{
	if (InDescription.IsEmpty())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Warning! Bounty description was null")));
		}

		UE_LOG(LogNexusSampleProject, Warning, TEXT("Warning! Bounty description was null"));
		return;
	}
	
	ensureMsgf(IsValid(BountyDescription), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	BountyDescription->SetText(FText::FromString(InDescription));
}

void UBountiesEntryUserWidget::SetBountyImage(FString InURL)
{
	if (InURL.IsEmpty()) 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Warning! Bounty image source was null")));
		}

		UE_LOG(LogNexusSampleProject, Warning, TEXT("Warning! Bounty image source was null"));
		return;
	}

	// Download image using url
	UAsyncTaskDownloadImage* DownloadImageTask = NewObject<UAsyncTaskDownloadImage>();
	DownloadImageTask->OnSuccess.AddDynamic(this, &UBountiesEntryUserWidget::OnGetTexture2D);
	DownloadImageTask->Start(InURL);
}

void UBountiesEntryUserWidget::SetBountyTitle(FString InTitle)
{
	if (InTitle.IsEmpty())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Warning! Bounty title was null")));
		}

		UE_LOG(LogNexusSampleProject, Warning, TEXT("Warning! Bounty title was null"));
		return;
	}

	ensureMsgf(IsValid(BountyTitle), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	BountyTitle->SetText(FText::FromString(InTitle));
}

void UBountiesEntryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(CollectBountyButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
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

void UBountiesEntryUserWidget::OnGetTexture2D(UTexture2DDynamic* _texture)
{
	ensureMsgf(IsValid(BountyImage), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	BountyImage->SetBrushFromTextureDynamic(_texture);
}
