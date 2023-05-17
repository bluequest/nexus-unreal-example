// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CreatorSupportUserWidget.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "NexusSampleProject/Public/NexusSampleProjectSaveGame.h"
#include "NexusSampleProjectHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

void UCreatorSupportUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void UCreatorSupportUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		BackButton->OnClicked.AddDynamic(this, &UCreatorSupportUserWidget::OnBackButtonPressed);
	}

	if (ensureMsgf(IsValid(SubmitButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		SubmitButton->OnClicked.AddDynamic(this, &UCreatorSupportUserWidget::OnSubmitButtonPressed);
	}

	if (ensureMsgf(IsValid(CreatorCodeInputTextBox), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		CreatorCodeInputTextBox->OnTextChanged.AddDynamic(this, &UCreatorSupportUserWidget::OnTextChanged);
	}

	// Load creator code
	UGameplayStatics::AsyncLoadGameFromSlot(
		SAVELOAD_SLOT_NAME, 
		GetOwningLocalPlayer()->GetLocalPlayerIndex(), 
		FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &UCreatorSupportUserWidget::OnAsyncLoadGameFromSlotComplete)
		);
}

void UCreatorSupportUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		RemoveFromParent();
		HUD->CreatorSupportWidget = nullptr;
	}
}

void UCreatorSupportUserWidget::OnSubmitButtonPressed()
{
	if (ensureMsgf(IsValid(CreatorCodeInputTextBox), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		if (CreatorCodeInputTextBox->GetText().IsEmpty()) 
		{
			return;
		}

		// #TODO ~Remove me! Just used for testing cat facts API
		OnGetGatFactsCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnGetCatFactsComplete);
		NexusSDK::FGetCatFactsRequest GetCatFactsRequest;
		GetCatFactsRequest.MaxLength = 32;
		GetCatFactsRequest.Limit = 32;
		NexusSDK::GetCatFacts(GetCatFactsRequest, OnGetGatFactsCompleteDelegate);
		// #TODO ~End remove me

		// #TODO Query Nexus creators using (https://api.nexus.gg/v1/attributions/creators) and check if any creator code matches player's input

		// Save the code on disk, so that during purchasing (transactions page) we can reference this code and call the create new sale attributed to a creator endpoint (https://api.nexus.gg/v1/attributions/transactions)
		SaveGameInstance = Cast<UNexusSampleProjectSaveGame>(UGameplayStatics::CreateSaveGameObject(UNexusSampleProjectSaveGame::StaticClass()));
		if (SaveGameInstance) 
		{
			SaveGameInstance->SaveSlotName = SAVELOAD_SLOT_NAME;
			SaveGameInstance->CreatorCode = CreatorCodeInputTextBox->GetText().ToString().ToUpper();
			SaveGameInstance->UserIndex = GetOwningLocalPlayer()->GetLocalPlayerIndex();
			UGameplayStatics::AsyncSaveGameToSlot(
				SaveGameInstance, 
				SaveGameInstance->SaveSlotName, 
				SaveGameInstance->UserIndex, 
				FAsyncSaveGameToSlotDelegate::CreateUObject(this, &UCreatorSupportUserWidget::OnAsyncSaveGameToSlotComplete)
				);
		}

		CreatorCodeInputTextBox->SetText(FText());
	}
}

void UCreatorSupportUserWidget::OnTextChanged(const FText& Text)
{
	// Set character limit. +1 is to account for left chop
	if (Text.ToString().Len() >= CreatorCodeCharacterLimit+1) 
	{
		CreatorCodeInputTextBox->SetText(FText::FromString(Text.ToString().LeftChop(1)));
	}
}

// #TODO Remove me! Just used for testing cat facts API
void UCreatorSupportUserWidget::OnGetCatFactsComplete(const NexusSDK::FGetCatFactsResponse& Response)
{
	if (Response.bSuccess)
	{
		// Logging
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Get cat facts successful!")));
		}

		FString FactListString = TEXT("");
		for (FString Fact : Response.Facts)
		{
			FactListString.Append(*Fact);
			FactListString.Append("\n");
		}

		UE_LOG(LogNexusSampleProject, Log, TEXT("Get cat facts successful! Fact List: \n%s"), *FactListString);
	}
	else 
	{
		UE_LOG(LogNexusSampleProject, Error, TEXT("Get cat facts failed!"));
	}
}
// #TODO ~End remove me

void UCreatorSupportUserWidget::OnAsyncSaveGameToSlotComplete(const FString& SlotName, const int32 UserIndex, bool bWasSuccessful)
{
	if (bWasSuccessful) 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Creator Code saved to settings!")));
		}

		UE_LOG(LogNexusSampleProject, Log, TEXT("Creator Code saved to disk"));
	}
	else 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Creator Code failed to save to settings!")));
		}

		UE_LOG(LogNexusSampleProject, Error, TEXT("Creator Code failed to save to disk"));
	}
}

void UCreatorSupportUserWidget::OnAsyncLoadGameFromSlotComplete(const FString& SlotName, const int32 UserIndex, USaveGame* OutSaveGame)
{
	if (UNexusSampleProjectSaveGame* SaveGameRef = Cast<UNexusSampleProjectSaveGame>(OutSaveGame)) 
	{
		if (ensureMsgf(IsValid(CreatorCodeInputTextBox), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
		{
			CreatorCodeInputTextBox->SetText(FText::FromString(*SaveGameRef->CreatorCode));

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Creator code loaded from save game!")));
			}

			UE_LOG(LogNexusSampleProject, Log, TEXT("Creator Code loaded from disk"));
		}
	}
}