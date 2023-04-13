// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CreatorSupportUserWidget.h"
#include "UI/BountiesUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Runtime/ApplicationCore/Public/HAL/PlatformApplicationMisc.h"
#include "Components/EditableTextBox.h"

void UCreatorSupportUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (IsValid(BackButton))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void UCreatorSupportUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(BackButton))
	{
		BackButton->OnClicked.AddDynamic(this, &UCreatorSupportUserWidget::OnBackButtonPressed);
	}

	if (IsValid(SubmitButton))
	{
		SubmitButton->OnClicked.AddDynamic(this, &UCreatorSupportUserWidget::OnSubmitButtonPressed);
	}

	if (IsValid(CopyCodeButton))
	{
		CopyCodeButton->OnClicked.AddDynamic(this, &UCreatorSupportUserWidget::OnCopyButtonPressed);
	}

	if (IsValid(LinkAccountButton))
	{
		LinkAccountButton->OnClicked.AddDynamic(this, &UCreatorSupportUserWidget::OnLinkAccountButtonPressed);
	}

	if (IsValid(ViewBoutniesButton))
	{
		ViewBoutniesButton->OnClicked.AddDynamic(this, &UCreatorSupportUserWidget::OnViewBountiesButtonPressed);
	}
	
	// #TODO Generate auth code (https://api.nexus.gg/v1/referrals/player/{playerId}/authCode)
	
	// #TODO Query player's creator code (https://api.nexus.gg/v1/referrals/code)

	// #TODO If none exists, generate code for a user (https://api.nexus.gg/v1/referrals/code)
	
	// #TODO Query bounties (https://api.nexus.gg/v1/bounties/), then populate entries
}

void UCreatorSupportUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
	{
		RemoveFromParent();
		CharacterRef->CreatorSupportWidget = nullptr;
	}
}

void UCreatorSupportUserWidget::OnSubmitButtonPressed()
{
	if (IsValid(CreatorCodeInputTextBox))
	{
		CreatorCodeInputTextBox->SetText(FText());
	}

	// #TODO Add SDK call
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Creator Code Submitted!")));
	}
}

void UCreatorSupportUserWidget::OnCopyButtonPressed()
{
	if (IsValid(PlayerReferralCode))
	{
		FPlatformApplicationMisc::ClipboardCopy(*PlayerReferralCode->GetText().ToString());
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Copied creator code!")));
	}
}

void UCreatorSupportUserWidget::OnLinkAccountButtonPressed()
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

void UCreatorSupportUserWidget::OnViewBountiesButtonPressed()
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
