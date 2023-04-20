// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ReferralsBountiesMenuUserWidget.h"
#include "UI/BountiesUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Runtime/ApplicationCore/Public/HAL/PlatformApplicationMisc.h"
#include "Components/EditableTextBox.h"

void UReferralsBountiesMenuUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ASSIGN_ENSURE_REASON))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void UReferralsBountiesMenuUserWidget::UpdatePlayerReferralCode()
{
	// #TODO Replace logic when Unreal SDK template is in.
	//OnGetReferralCodeCompleteDelegate.BindUObject(this, &UReferralsBountiesMenuUserWidget::OnGetPlayerReferralCodeComplete);
	//NexusSDK::GetPlayerReferralCode(32, 32, OnGetReferralCodeCompleteDelegate);

	// #TODO Replace logic below when NexusSDK::GetPlayerReferralCode is in
	FString TestString = TEXT("Testing!");
	OnGetPlayerReferralCodeComplete(TestString, true);
}

void UReferralsBountiesMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ASSIGN_ENSURE_REASON))
	{
		BackButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnBackButtonPressed);
	}

	if (ensureMsgf(IsValid(SubmitButton), BP_ASSIGN_ENSURE_REASON))
	{
		SubmitButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnSubmitButtonPressed);
	}

	if (ensureMsgf(IsValid(CopyCodeButton), BP_ASSIGN_ENSURE_REASON))
	{
		CopyCodeButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnCopyButtonPressed);
	}

	if (ensureMsgf(IsValid(LinkAccountButton), BP_ASSIGN_ENSURE_REASON))
	{
		LinkAccountButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnLinkAccountButtonPressed);
	}

	if (ensureMsgf(IsValid(ViewBoutniesButton), BP_ASSIGN_ENSURE_REASON))
	{
		ViewBoutniesButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnViewBountiesButtonPressed);
	}

	// #TODO Generate auth code (https://api.nexus.gg/v1/referrals/player/{playerId}/authCode)

	// #TODO Query player's referral code (https://api.nexus.gg/v1/referrals/player/{playerId}/code)
	UpdatePlayerReferralCode();

	// #TODO If none exists, generate code for a user (https://api.nexus.gg/v1/referrals/code)

	// #TODO Query bounties (https://api.nexus.gg/v1/bounties/), then populate entries
}

void UReferralsBountiesMenuUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
	{
		RemoveFromParent();
		CharacterRef->ReferralsBountiesMenuWidget = nullptr;
	}
}

void UReferralsBountiesMenuUserWidget::OnSubmitButtonPressed()
{
	if (ensureMsgf(IsValid(ReferralCodeInputTextBox), BP_ASSIGN_ENSURE_REASON))
	{
		if (ReferralCodeInputTextBox->GetText().IsEmpty())
		{
			return;
		}

		// #TODO Replace logic when Unreal SDK template is in.
		//OnSubmitReferralCodeCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnSubmitReferralCodeComplete);
		//NexusSDK::SubmitReferralCode(FString GroupId, OnSubmitReferralCodeCompleteDelegate);

		// #TODO Replace logic below when NexusSDK::SubmitReferralCode is in
		FString TestGroupId = TEXT("TestGroupId");
		FString TestGroupName = TEXT("TestGroupName");
		OnSubmitReferralCodeComplete(TestGroupId, TestGroupName, true);
	
		ReferralCodeInputTextBox->SetText(FText());
	}
}

void UReferralsBountiesMenuUserWidget::OnCopyButtonPressed()
{
	if (ensureMsgf(IsValid(PlayerReferralCode), BP_ASSIGN_ENSURE_REASON))
	{
		FPlatformApplicationMisc::ClipboardCopy(*PlayerReferralCode->GetText().ToString());
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Referral code copied!")));
	}
}

void UReferralsBountiesMenuUserWidget::OnLinkAccountButtonPressed()
{
	ensureMsgf(IsValid(LinkAccountWidgetClass), BP_ASSIGN_ENSURE_REASON);
	ULinkAccountUserWidget* LinkAccountWidgetRef = CreateWidget<ULinkAccountUserWidget>(GetWorld(), LinkAccountWidgetClass);
	if (IsValid(LinkAccountWidgetRef))
	{
		LinkAccountWidgetRef->AddToViewport();

		if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
		{
			CharacterRef->LinkAccountWidget = LinkAccountWidgetRef;
		}
	}
}

void UReferralsBountiesMenuUserWidget::OnViewBountiesButtonPressed()
{
	ensureMsgf(IsValid(BountiesWidgetClass), BP_ASSIGN_ENSURE_REASON);
	UBountiesUserWidget* BountiesWidgetRef = CreateWidget<UBountiesUserWidget>(GetWorld(), BountiesWidgetClass);
	if (IsValid(BountiesWidgetRef))
	{
		BountiesWidgetRef->AddToViewport();

		if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
		{
			CharacterRef->BountiesWidget = BountiesWidgetRef;
		}
	}
}

void UReferralsBountiesMenuUserWidget::OnGetPlayerReferralCodeComplete(FString& ReferralCode, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (ensureMsgf(IsValid(PlayerReferralCode), BP_ASSIGN_ENSURE_REASON))
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

void UReferralsBountiesMenuUserWidget::OnSubmitReferralCodeComplete(FString& GroupId, FString& GroupName, /* FReferralStruct ReferralInfo, */ bool bWasSuccessful)
{
	if (bWasSuccessful && !GroupId.IsEmpty() && !GroupName.IsEmpty())
	{
		// Logging
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Submit creator (referral) code success! Response - GroupId: %s, GroupName: %s"), *GroupId, *GroupName));
		}

		UE_LOG(LogNexusSampleProject, Log, TEXT("Submit referral code succeeded! Response - GroupId: %s, GroupName : %s"), *GroupId, *GroupName);
	}
	else
	{
		UE_LOG(LogNexusSampleProject, Error, TEXT("Submit referral code failed!"));
	}
}
