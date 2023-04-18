// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LinkAccountUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void ULinkAccountUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(BackButton))
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

	if (IsValid(BackButton))
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
	if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
	{
		RemoveFromParent();
		CharacterRef->LinkAccountWidget = nullptr;
	}
}

void ULinkAccountUserWidget::OnGetPlayerReferralCodeComplete(FString& ReferralCode, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (ensure(IsValid(PlayerReferralCode)))
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
		UE_LOG(LogNexusSampleProject, Warning, TEXT("Get player referral code failed!"));
	}
}