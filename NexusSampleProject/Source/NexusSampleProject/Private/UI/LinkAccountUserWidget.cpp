// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LinkAccountUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "NexusSampleProjectHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void ULinkAccountUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		BackButton->OnClicked.AddDynamic(this, &ULinkAccountUserWidget::OnBackButtonPressed);
	}

	// #TODO Query player's referral code (https://api.nexus.gg/v1/referrals/player/{playerId}/code)
	UpdatePlayerReferralCode();
}

void ULinkAccountUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void ULinkAccountUserWidget::UpdatePlayerReferralCode()
{
	// #TODO Replace logic when Unreal SDK template is in.
	//OnGetReferralCodeCompleteDelegate.BindUObject(this, &UReferralsBountiesMenuUserWidget::OnGetPlayerReferralCodeComplete);
	//NexusSDK::GetPlayerReferralCode(32, 32, OnGetReferralCodeCompleteDelegate);

	// #TODO Replace logic below when NexusSDK::GetPlayerReferralCode is in
	FString TestString = TEXT("Testing!");
	OnGetPlayerReferralCodeComplete(TestString, true);
}

void ULinkAccountUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		RemoveFromParent();
		HUD->LinkAccountWidget = nullptr;
	}
}

void ULinkAccountUserWidget::OnGetPlayerReferralCodeComplete(FString& ReferralCode, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (ensureMsgf(IsValid(PlayerReferralCode), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
		{
			PlayerReferralCode->SetText(FText::FromString(ReferralCode));
		}

		// Logging
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Get player referral code succeeded! ReferralCode: %s"), *ReferralCode));
		}

		UE_LOG(LogNexusSampleProject, Log, TEXT("Get player referral code succeeded! ReferralCode: %s"), *ReferralCode);
	}
	else 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Get player referral code failed!"));
		}

		UE_LOG(LogNexusSampleProject, Error, TEXT("Get player referral code failed!"));
	}
}