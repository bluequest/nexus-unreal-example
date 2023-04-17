// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ReferralsBountiesMenuUserWidget.h"
#include "UI/BountiesUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Runtime/ApplicationCore/Public/HAL/PlatformApplicationMisc.h"
#include "Components/EditableTextBox.h"

void UReferralsBountiesMenuUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (IsValid(BackButton))
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

	if (IsValid(BackButton))
	{
		BackButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnBackButtonPressed);
	}

	if (IsValid(SubmitButton))
	{
		SubmitButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnSubmitButtonPressed);
	}

	if (IsValid(CopyCodeButton))
	{
		CopyCodeButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnCopyButtonPressed);
	}

	if (IsValid(LinkAccountButton))
	{
		LinkAccountButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnLinkAccountButtonPressed);
	}

	if (IsValid(ViewBoutniesButton))
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
	if (IsValid(ReferralCodeInputTextBox))
	{
		ReferralCodeInputTextBox->SetText(FText());
	}

	// #TODO Replace logic when Unreal SDK template is in.
	//OnSubmitReferralCodeCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnSubmitReferralCodeComplete);
	//NexusSDK::SubmitReferralCode(32, 32, OnSubmitReferralCodeCompleteDelegate);

	// #TODO Replace logic below when NexusSDK::SubmitReferralCode is in
	FString TestGroupId = TEXT("TestGroupId");
	FString TestGroupName = TEXT("TestGroupName");
	OnSubmitReferralCodeComplete(TestGroupId, TestGroupName, true);
}

void UReferralsBountiesMenuUserWidget::OnCopyButtonPressed()
{
	if (IsValid(PlayerReferralCode))
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
	ensure(IsValid(LinkAccountWidgetClass));
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
	ensure(IsValid(BountiesWidgetClass));
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
		if (ensure(IsValid(PlayerReferralCode))) 
		{
			PlayerReferralCode->SetText(FText::FromString(ReferralCode));
		}

		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("GetReferralCode successful!")));
		}
	}
}

void UReferralsBountiesMenuUserWidget::OnSubmitReferralCodeComplete(FString& GroupId, FString& GroupName, /* FReferralStruct ReferralInfo, */ bool bWasSuccessful)
{
	if (bWasSuccessful && !GroupId.IsEmpty() && !GroupName.IsEmpty())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Submit referral code success! Response - GroupId: %s, GroupName: %s"), *GroupId, *GroupName));
		}
	}
}
