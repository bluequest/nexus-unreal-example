// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ReferralsBountiesMenuUserWidget.h"
#include "UI/BountiesUserWidget.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "NexusSampleProjectHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
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
	// For an example, we will use the 1st creator found in the GetCreators call, and assign that data to the player to mimic login.
	// 
	// In a real project, after a login system has been implemented, a player should have their username/playerId at this point,
	// and should be used in replacement of the example for querying the player's referral/creator code

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

void UReferralsBountiesMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

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

		// #TODO Replace logic when Unreal SDK template is in.
		//OnSubmitReferralCodeCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnSubmitReferralCodeComplete);
		//NexusSDK::SubmitReferralCode(FString GroupId, OnSubmitReferralCodeCompleteDelegate);

		// #TODO Replace logic below when NexusSDK::SubmitReferralCode is in
		//FString TestGroupId = TEXT("TestGroupId");
		//FString TestGroupName = TEXT("TestGroupName");
		//OnSubmitReferralCodeComplete(TestGroupId, TestGroupName, true);
	
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

	// For an example, we will use the 1st creator found in the GetCreators call, and assign that data to the player to mimic login.
	// We will then use that id to query the player's creator/referral code
	if (Response.creators.Num() > 0) 
	{
		FNexusReferralGetReferralInfoByPlayerIdRequestParams RequestParams;
		RequestParams.playerId = Response.creators[0].id;
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

void UReferralsBountiesMenuUserWidget::OnGetReferralInfoByPlayerId200ResponseComplete(const FNexusReferralGetReferralInfoByPlayerId200Response& Response)
{
	UE_LOG(LogNexusSampleProject, Log, TEXT("GetReferralInfoByPlayerId returned a successful response"));

	if (ensureMsgf(IsValid(PlayerReferralCode), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		// Just use 1st found referral code
		if (Response.referralCodes.Num() > 0) 
		{
			PlayerReferralCode->SetText(FText::FromString(Response.referralCodes[0].code).ToUpper());
		}
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

/*
void UReferralsBountiesMenuUserWidget::OnSubmitReferralCodeComplete(FString& GroupId, FString& GroupName,  FReferralStruct ReferralInfo,  bool bWasSuccessful)
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
*/