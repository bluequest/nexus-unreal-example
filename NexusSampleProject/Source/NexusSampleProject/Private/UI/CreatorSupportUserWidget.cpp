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

	// Query Nexus creators to be used to check if any creator code matches player's input in UCreatorSupportUserWidget::OnSubmitButtonPressed
	FNexusAttributionGetCreatorsRequestParams RequestParams;
	RequestParams.groupId = TEXT("");
	RequestParams.page = 1;
	RequestParams.pageSize = 100;

	FNexusAttributionAPI::GetCreators(
		RequestParams,
		FNexusAttributionAPI::FOnGetCreators200ResponseCallback::CreateUObject(this, &UCreatorSupportUserWidget::OnGetCreatorsComplete),
		FNexusOnHttpErrorDelegate::CreateUObject(this, &UCreatorSupportUserWidget::OnGetCreatorsError)	
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

		// Check if the player's input matches any creator codes found on the backend
		bool bCreatorCodeFound = false;
		for (FString QueriedCreatorCode : CreatorCodeList) 
		{
			if (QueriedCreatorCode.ToUpper() == CreatorCodeInputTextBox->GetText().ToString().ToUpper()) 
			{
				bCreatorCodeFound = true;
			}
		}		
		
		if (!bCreatorCodeFound) 
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Creator code: %s was not found on the backend. Try again with a different code."), *CreatorCodeInputTextBox->GetText().ToString().ToUpper()));
				
			}

			UE_LOG(LogNexusSampleProject, Warning, TEXT("Creator code: %s was not found"), *CreatorCodeInputTextBox->GetText().ToString().ToUpper());
			return;
		}

		// If the code was found, save the code on disk, so that shop/store integration can reference this code to attribute to creators
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

void UCreatorSupportUserWidget::OnAsyncSaveGameToSlotComplete(const FString& SlotName, const int32 UserIndex, bool bWasSuccessful)
{
	if (bWasSuccessful) 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valid Creator Code was entered! Code was saved to settings.")));
		}

		UE_LOG(LogNexusSampleProject, Log, TEXT("Valid Creator Code was entered! Code was saved to settings."));
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

void UCreatorSupportUserWidget::OnGetCreatorsComplete(const FNexusAttributionGetCreators200Response& Response)
{
	UE_LOG(LogNexusSampleProject, Log, TEXT("GetCreators returned a successful response"));

	// For each creator, get their current referral/creator code and store it for player validation input check in UCreatorSupportUserWidget::OnSubmitButtonPressed
	for (FNexusAttributionCreator Creator : Response.creators) 
	{
		FNexusReferralGetReferralInfoByPlayerIdRequestParams RequestParams;
		RequestParams.playerId = Creator.id;
		RequestParams.page = 1;
		RequestParams.pageSize = 100;

		FNexusReferralAPI::FOnGetReferralInfoByPlayerIdResponse OnGetReferralInfoByPlayerIdResponse;
		OnGetReferralInfoByPlayerIdResponse.On200Response.BindUObject(this, &UCreatorSupportUserWidget::OnGetReferralInfoByPlayerId200ResponseComplete);
		OnGetReferralInfoByPlayerIdResponse.On400Response.BindUObject(this, &UCreatorSupportUserWidget::OnGetReferralInfoByPlayerId400ResponseComplete);

		FNexusReferralAPI::GetReferralInfoByPlayerId(
			RequestParams, 
			OnGetReferralInfoByPlayerIdResponse,
			FNexusOnHttpErrorDelegate::CreateUObject(this, &UCreatorSupportUserWidget::OnGetReferralInfoByPlayerIdError)
			);
	}
}

void UCreatorSupportUserWidget::OnGetCreatorsError(int32 ErrorCode)
{
	// #TODO display widget on screen message that get creators failed, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Failed to GetCreators. ErrorCode: %d"), ErrorCode));
	}

	UE_LOG(LogNexusSampleProject, Error, TEXT("Failed to GetCreators. ErrorCode: %d"), ErrorCode);
}

void UCreatorSupportUserWidget::OnGetReferralInfoByPlayerId200ResponseComplete(const FNexusReferralGetReferralInfoByPlayerId200Response& Response)
{
	UE_LOG(LogNexusSampleProject, Log, TEXT("GetReferralInfoByPlayerId returned a successful response"));
	
	// Store code on a successful response
	for (FNexusReferralReferralCodeResponse ReferralCode : Response.referralCodes) 
	{
		CreatorCodeList.AddUnique(ReferralCode.code);
	}
}

void UCreatorSupportUserWidget::OnGetReferralInfoByPlayerId400ResponseComplete(const FNexusReferralReferralError& Response)
{
	// #TODO display widget on screen message that get creator code returned 400, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnGetReferralInfoByPlayerId returned a 400 error with message: %s"), *Response.code));
	}

	UE_LOG(LogNexusSampleProject, Error, TEXT("OnGetReferralInfoByPlayerId returned a 400 error with message: %s"), *Response.code);
}

void UCreatorSupportUserWidget::OnGetReferralInfoByPlayerIdError(int32 ErrorCode)
{
	// #TODO display widget on screen message that get creator code failed, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Failed to GetCreatorCode. ErrorCode: %d"), ErrorCode));
	}

	UE_LOG(LogNexusSampleProject, Error, TEXT("Failed to GetCreatorCode. ErrorCode: %d"), ErrorCode);
}