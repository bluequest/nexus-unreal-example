// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ReferralsBountiesMenuUserWidget.h"
#include "UI/BountiesUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "NexusSampleProject/Public/NexusSampleProjectSaveGame.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "NexusSampleProjectHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Runtime/ApplicationCore/Public/HAL/PlatformApplicationMisc.h"
#include "Components/EditableTextBox.h"

void UReferralsBountiesMenuUserWidget::SetupInitialFocus(APlayerController* Controller)
{
	FInputModeGameAndUI GameAndUIMode;
	GameAndUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void UReferralsBountiesMenuUserWidget::UpdatePlayerReferralCode()
{
	// #NOTE Just for this example project, we will use the 1st creator found in the GetCreators call, and assign that data to the player to mimic login.
	// 
	// In a real project, after a login system has been implemented, a player should have their username/playerId at this point,
	// which then should be used when querying the player's referral/creator code.

	FNexusAttributionGetCreatorsRequestParams RequestParams;
	RequestParams.groupId = TEXT("");
	RequestParams.page = 1;
	RequestParams.pageSize = 100;

	FNexusAttributionAPI::GetCreators(
		RequestParams,
		FNexusAttributionAPI::FOnGetCreators200ResponseCallback::CreateUObject(this, &UReferralsBountiesMenuUserWidget::OnGetCreatorsComplete),
		FNexusOnHttpErrorDelegate::CreateUObject(this, &UReferralsBountiesMenuUserWidget::OnGetCreatorsError)
	);
}

void UReferralsBountiesMenuUserWidget::UpdateSavedReferralCode()
{
	// Load referral code
	UGameplayStatics::AsyncLoadGameFromSlot(
		SAVELOAD_SLOT_NAME,
		GetOwningLocalPlayer()->GetLocalPlayerIndex(),
		FAsyncLoadGameFromSlotDelegate::CreateUObject(this, &UReferralsBountiesMenuUserWidget::OnAsyncLoadGameFromSlotComplete)
	);
}

void UReferralsBountiesMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// For testing referral progress, set referral progress goal to 5
	ReferralProgressGoal = 5;

	if (ensureMsgf(IsValid(BackButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		BackButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnBackButtonPressed);
	}

	if (ensureMsgf(IsValid(SubmitButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		SubmitButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnSubmitButtonPressed);
	}

	if (ensureMsgf(IsValid(CopyCodeButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		CopyCodeButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnCopyButtonPressed);
	}

	if (ensureMsgf(IsValid(LinkAccountButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		LinkAccountButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnLinkAccountButtonPressed);
	}

	if (ensureMsgf(IsValid(ViewBoutniesButton), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		ViewBoutniesButton->OnClicked.AddDynamic(this, &UReferralsBountiesMenuUserWidget::OnViewBountiesButtonPressed);
	}

	// Query player's referral code
	UpdatePlayerReferralCode();

	// Similar to UCreatorSupportUserWidget, display the saved referral/creator code in the ReferralCodeInputTextBox if applicable
	UpdateSavedReferralCode();
}

void UReferralsBountiesMenuUserWidget::OnBackButtonPressed()
{
	if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		RemoveFromParent();
		HUD->ReferralsBountiesMenuWidget = nullptr;
	}
}

void UReferralsBountiesMenuUserWidget::OnSubmitButtonPressed()
{
	if (ensureMsgf(IsValid(ReferralCodeInputTextBox), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		if (ReferralCodeInputTextBox->GetText().IsEmpty())
		{
			return;
		}

		if (LocalPlayerReferralCode == ReferralCodeInputTextBox->GetText().ToString().ToUpper()) 
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("You cannot refer yourself! Try again with a different code.")));
			}

			UE_LOG(LogNexusSampleProject, Warning, TEXT("You cannot refer yourself! Try again with a different code."));
			return;
		}
		
		// Similar to UCreatorSupportUserWidget, check if the player's input matches any referral codes found on the backend, 
		// and if so save the code on disk so that shop/store integration can reference this code to attribute to creators
		bool bReferralCodeFound = false;
		for (FString QueriedReferralCode : ReferralCodeList)
		{
			FString Compare1 = QueriedReferralCode.ToUpper();
			FString Compare2 = ReferralCodeInputTextBox->GetText().ToString().ToUpper();
			if (QueriedReferralCode.ToUpper() == ReferralCodeInputTextBox->GetText().ToString().ToUpper())
			{
				bReferralCodeFound = true;
			}
		}

		if (!bReferralCodeFound)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Referral code: %s was not found on the backend. Try again with a different code."), *ReferralCodeInputTextBox->GetText().ToString().ToUpper()));
			}

			UE_LOG(LogNexusSampleProject, Warning, TEXT("Referral code: %s was not found"), *ReferralCodeInputTextBox->GetText().ToString().ToUpper());
			return;
		}

		SaveGameInstance = Cast<UNexusSampleProjectSaveGame>(UGameplayStatics::CreateSaveGameObject(UNexusSampleProjectSaveGame::StaticClass()));
		if (SaveGameInstance)
		{
			SaveGameInstance->SaveSlotName = SAVELOAD_SLOT_NAME;
			SaveGameInstance->CreatorCode = ReferralCodeInputTextBox->GetText().ToString().ToUpper();
			SaveGameInstance->UserIndex = GetOwningLocalPlayer()->GetLocalPlayerIndex();
			UGameplayStatics::AsyncSaveGameToSlot(
				SaveGameInstance,
				SaveGameInstance->SaveSlotName,
				SaveGameInstance->UserIndex,
				FAsyncSaveGameToSlotDelegate::CreateUObject(this, &UReferralsBountiesMenuUserWidget::OnAsyncSaveGameToSlotComplete)
			);
		}

		ReferralCodeInputTextBox->SetText(FText());
	}
}

void UReferralsBountiesMenuUserWidget::OnCopyButtonPressed()
{
	if (ensureMsgf(IsValid(PlayerReferralCode), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
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
	ensureMsgf(IsValid(LinkAccountWidgetClass), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	ULinkAccountUserWidget* LinkAccountWidgetRef = CreateWidget<ULinkAccountUserWidget>(GetWorld(), LinkAccountWidgetClass);
	if (IsValid(LinkAccountWidgetRef))
	{
		LinkAccountWidgetRef->AddToViewport();

		if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
		{
			HUD->LinkAccountWidget = LinkAccountWidgetRef;
		}
	}
}

void UReferralsBountiesMenuUserWidget::OnViewBountiesButtonPressed()
{
	ensureMsgf(IsValid(BountiesWidgetClass), BP_ENSURE_REASON_INVALID_CLASS_WIDGET);
	UBountiesUserWidget* BountiesWidgetRef = CreateWidget<UBountiesUserWidget>(GetWorld(), BountiesWidgetClass);
	if (IsValid(BountiesWidgetRef))
	{
		BountiesWidgetRef->AddToViewport();

		if (ANexusSampleProjectHUD* HUD = Cast<ANexusSampleProjectHUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
		{
			HUD->BountiesWidget = BountiesWidgetRef;
		}
	}
}

void UReferralsBountiesMenuUserWidget::OnGetCreatorsComplete(const FNexusAttributionGetCreators200Response& Response)
{
	UE_LOG(LogNexusSampleProject, Log, TEXT("GetCreators returned a successful response"));

	// #NOTE For an example, we will use the 1st creator found in the GetCreators call, and assign that data to the player to mimic login.
	if (Response.creators.Num() >0)
	{
		FNexusReferralGetReferralInfoByPlayerIdRequestParams RequestParams;
		RequestParams.playerId = Response.creators[0].id;
		RequestParams.page = 1;
		RequestParams.pageSize = 100;

		FNexusReferralAPI::FOnGetReferralInfoByPlayerIdResponse OnGetReferralInfoByPlayerIdResponse;
		OnGetReferralInfoByPlayerIdResponse.On200Response.BindUObject(this, &UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerIdFirstCreator200ResponseComplete);
		OnGetReferralInfoByPlayerIdResponse.On400Response.BindUObject(this, &UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerId400ResponseComplete);

		FNexusReferralAPI::GetReferralInfoByPlayerId(
			RequestParams,
			OnGetReferralInfoByPlayerIdResponse,
			FNexusOnHttpErrorDelegate::CreateUObject(this, &UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerIdError)
		);
	}	
	
	// For each creator, get their current referral/creator code and store it for player validation input check in UCreatorSupportUserWidget::OnSubmitButtonPressed
	for (FNexusAttributionCreator Creator : Response.creators)
	{
		FNexusReferralGetReferralInfoByPlayerIdRequestParams RequestParams;
		RequestParams.playerId = Creator.id;
		RequestParams.page = 1;
		RequestParams.pageSize = 100;

		FNexusReferralAPI::FOnGetReferralInfoByPlayerIdResponse OnGetReferralInfoByPlayerIdResponse;
		OnGetReferralInfoByPlayerIdResponse.On200Response.BindUObject(this, &UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerId200ResponseComplete);
		OnGetReferralInfoByPlayerIdResponse.On400Response.BindUObject(this, &UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerId400ResponseComplete);

		FNexusReferralAPI::GetReferralInfoByPlayerId(
			RequestParams,
			OnGetReferralInfoByPlayerIdResponse,
			FNexusOnHttpErrorDelegate::CreateUObject(this, &UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerIdError)
		);
	}
}

void UReferralsBountiesMenuUserWidget::OnGetCreatorsError(int32 ErrorCode)
{
	// #TODO display widget on screen message that get creators failed, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Failed to GetCreators. ErrorCode: %d"), ErrorCode));
	}

	UE_LOG(LogNexusSampleProject, Error, TEXT("Failed to GetCreators. ErrorCode: %d"), ErrorCode);
}

void UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerIdFirstCreator200ResponseComplete(const FNexusReferralGetReferralInfoByPlayerId200Response& Response)
{
	if (ensureMsgf(IsValid(PlayerReferralCode), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		// #NOTE For example, we will use the 1st creator found in the GetCreators call, and assign that data to the player to mimic login
		if (Response.referralCodes.Num() > 0 && LocalPlayerReferralCode.IsEmpty())
		{
			LocalPlayerReferralCode = Response.referralCodes[0].code;
			PlayerReferralCode->SetText(FText::FromString(Response.referralCodes[0].code).ToUpper());
		}

		if (Response.referrals.Num() > -1) 
		{
			ReferralProgressBar->SetPercent(Response.referrals.Num()/ReferralProgressGoal);
		}
	}
}

void UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerId200ResponseComplete(const FNexusReferralGetReferralInfoByPlayerId200Response& Response)
{
	UE_LOG(LogNexusSampleProject, Log, TEXT("GetReferralInfoByPlayerId returned a successful response"));

	// Store code on a successful response
	for (FNexusReferralReferralCodeResponse ReferralCode : Response.referralCodes)
	{
		ReferralCodeList.AddUnique(ReferralCode.code);
	}
}

void UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerId400ResponseComplete(const FNexusReferralReferralError& Response)
{
	// #TODO display widget on screen message that get creator code returned 400, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnGetReferralInfoByPlayerId returned a 400 error with message: %s"), *Response.code));
	}

	UE_LOG(LogNexusSampleProject, Error, TEXT("OnGetReferralInfoByPlayerId returned a 400 error with message: %s"), *Response.code);
}

void UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerIdError(int32 ErrorCode)
{
	// #TODO display widget on screen message that get creator code failed, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Failed to GetCreatorCode. ErrorCode: %d"), ErrorCode));
	}

	UE_LOG(LogNexusSampleProject, Error, TEXT("Failed to GetCreatorCode. ErrorCode: %d"), ErrorCode);
}

void UReferralsBountiesMenuUserWidget::OnAsyncSaveGameToSlotComplete(const FString& SlotName, const int32 UserIndex, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Valid Referral Code was entered! Code was saved to settings.")));
		}

		UE_LOG(LogNexusSampleProject, Log, TEXT("Valid Referral Code was entered! Code was saved to settings."));
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Referral Code failed to save to settings!")));
		}

		UE_LOG(LogNexusSampleProject, Error, TEXT("Referral Code failed to save to disk"));
	}
}

void UReferralsBountiesMenuUserWidget::OnAsyncLoadGameFromSlotComplete(const FString& SlotName, const int32 UserIndex, USaveGame* OutSaveGame)
{
	if (UNexusSampleProjectSaveGame* SaveGameRef = Cast<UNexusSampleProjectSaveGame>(OutSaveGame))
	{
		if (ensureMsgf(IsValid(ReferralCodeInputTextBox), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
		{
			ReferralCodeInputTextBox->SetText(FText::FromString(*SaveGameRef->CreatorCode));

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Creator code loaded from save game!")));
			}

			UE_LOG(LogNexusSampleProject, Log, TEXT("Creator Code loaded from disk"));
		}
	}
}