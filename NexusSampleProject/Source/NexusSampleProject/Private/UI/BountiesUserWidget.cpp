// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BountiesUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "Kismet/GameplayStatics.h"
#include "NexusSampleProjectHUD.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"

void UBountiesUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void UBountiesUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		BackButton->OnClicked.AddDynamic(this, &UBountiesUserWidget::OnBackButtonPressed);
	}

	// Query bounties then then populate the response as a bounty entry in the BountiesReferralScrollBox
	FNexusBountyGetBountiesRequestParams RequestParams;
	RequestParams.page = 1;
	RequestParams.pageSize = 100;

	FNexusBountyAPI::FOnGetBountiesResponse GetBountiesResponse;
	GetBountiesResponse.On200Response.BindUObject(this, &UBountiesUserWidget::OnGetBounties200ResponseComplete);
	GetBountiesResponse.On400Response.BindUObject(this, &UBountiesUserWidget::OnGetBounties400ResponseComplete);
	
	FNexusBountyAPI::GetBounties(
		RequestParams,
		GetBountiesResponse,
		FNexusOnHttpErrorDelegate::CreateUObject(this, &UBountiesUserWidget::OnGetBountiesError)
		);

	BountiesReferralScrollBox->ClearChildren();
}

void UBountiesUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		RemoveFromParent();
		HUD->BountiesWidget = nullptr;
	}
}

void UBountiesUserWidget::OnGetBounties200ResponseComplete(const FNexusBountyGetBounties200Response& Response)
{
	for (FNexusBountyBounty BountyEntry : Response.bounties) 
	{
		ensureMsgf(IsValid(BountiesEntryWidgetClass), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
		UBountiesEntryUserWidget* BountiesEntryWidgetRef = CreateWidget<UBountiesEntryUserWidget>(GetWorld(), BountiesEntryWidgetClass);
		if (IsValid(BountiesEntryWidgetRef))
		{
			BountiesEntryWidgetRef->SetBountyDescription(BountyEntry.description);	
			BountiesEntryWidgetRef->SetBountyImage(BountyEntry.imageSrc);
			BountiesReferralScrollBox->AddChild(BountiesEntryWidgetRef);
		}
	}
	
	UE_LOG(LogNexusSampleProject, Log, TEXT("GetBounties returned a successful response"));
}

void UBountiesUserWidget::OnGetBounties400ResponseComplete(const FNexusBountyBountyError& Response)
{
	// #TODO display widget on screen message that get bounties failed, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GetBounties returned a 400 error with message: %s"), *Response.code));
	}

	UE_LOG(LogNexusSampleProject, Error, TEXT("GetBounties returned a 400 error with message: %s"), *Response.code);
}

void UBountiesUserWidget::OnGetBountiesError(int32 ErrorCode)
{
	// #TODO display widget on screen message that get bounties failed, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Failed to GetBounties. ErrorCode: %d"), ErrorCode));
	}

	UE_LOG(LogNexusSampleProject, Error, TEXT("Failed to GetBounties. ErrorCode: %d"), ErrorCode);
}