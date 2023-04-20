// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemShopMenuUserWidget.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "NexusSampleProject/Public/NexusSampleProjectSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void UItemShopMenuUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ASSIGN_ENSURE_REASON))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void UItemShopMenuUserWidget::UpdateCreatorCodeDisplay()
{
	// Load creator code
	UGameplayStatics::AsyncLoadGameFromSlot(
		SAVELOAD_SLOT_NAME,
		GetOwningLocalPlayer()->GetLocalPlayerIndex(),
		FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &UItemShopMenuUserWidget::OnAsyncLoadGameFromSlotComplete)
	);
}

void UItemShopMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ASSIGN_ENSURE_REASON))
	{
		BackButton->OnClicked.AddDynamic(this, &UItemShopMenuUserWidget::OnBackButtonPressed);
	}

	UpdateCreatorCodeDisplay();
}

void UItemShopMenuUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectCharacter* CharacterRef = Cast<ANexusSampleProjectCharacter>(GetOwningPlayerPawn()))
	{
		RemoveFromParent();
		CharacterRef->ItemShopMenuWidget = nullptr;
	}
}

void UItemShopMenuUserWidget::OnAsyncLoadGameFromSlotComplete(const FString& SlotName, const int32 UserIndex, USaveGame* OutSaveGame)
{
	if (UNexusSampleProjectSaveGame* SaveGameRef = Cast<UNexusSampleProjectSaveGame>(OutSaveGame))
	{
		if (ensureMsgf(IsValid(CreatorCodeTextBox), BP_ASSIGN_ENSURE_REASON)) 
		{
			CreatorCodeTextBox->SetText(FText::FromString(*SaveGameRef->CreatorCode));

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Creator code loaded from save game!")));
			}

			UE_LOG(LogNexusSampleProject, Log, TEXT("Creator Code loaded from disk"));
		}
	}
}