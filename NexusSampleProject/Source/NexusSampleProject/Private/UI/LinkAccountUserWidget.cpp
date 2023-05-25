// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LinkAccountUserWidget.h"
#include "NexusSampleProject/Public/NexusSampleProjectSaveGame.h"
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
	// Load referral code
	UGameplayStatics::AsyncLoadGameFromSlot(
		SAVELOAD_SLOT_NAME,
		GetOwningLocalPlayer()->GetLocalPlayerIndex(),
		FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &ULinkAccountUserWidget::OnAsyncLoadGameFromSlotComplete)
	);
}

void ULinkAccountUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		RemoveFromParent();
		HUD->LinkAccountWidget = nullptr;

		if (IsValid(HUD->ReferralsBountiesMenuWidget)) 
		{
			HUD->ReferralsBountiesMenuWidget->SetupInitialFocus(GetOwningPlayer());
		}
	}
}

void ULinkAccountUserWidget::OnAsyncLoadGameFromSlotComplete(const FString& SlotName, const int32 UserIndex, USaveGame* OutSaveGame)
{
	if (UNexusSampleProjectSaveGame* SaveGameRef = Cast<UNexusSampleProjectSaveGame>(OutSaveGame))
	{
		if (ensureMsgf(IsValid(PlayerReferralCode), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
		{
			PlayerReferralCode->SetText(FText::FromString(*SaveGameRef->CreatorCode));

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Referral code loaded from save game!")));
			}

			UE_LOG(LogNexusSampleProject, Log, TEXT("Referral Code loaded from disk"));
		}
	}
}
