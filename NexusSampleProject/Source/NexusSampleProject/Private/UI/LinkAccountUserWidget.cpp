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

void ULinkAccountUserWidget::UpdatePlayerReferralCode()
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
		FNexusAttributionAPI::FOnGetCreators200ResponseCallback::CreateUObject(this, &ULinkAccountUserWidget::OnGetCreatorsComplete),
		FNexusOnHttpErrorDelegate::CreateUObject(this, &ULinkAccountUserWidget::OnGetCreatorsError)
	);
}

void ULinkAccountUserWidget::OnGetCreatorsComplete(const FNexusAttributionGetCreators200Response& Response)
{
	UE_LOG(LogTemp, Log, TEXT("GetCreators returned a successful response"));

	// #NOTE For an example, we will use the 1st creator found in the GetCreators call, and assign that data to the player to mimic login.
	if (Response.creators.Num() > 0)
	{
		FNexusReferralGetReferralInfoByPlayerIdRequestParams RequestParams;
		RequestParams.playerId = Response.creators[0].id;
		RequestParams.page = 1;
		RequestParams.pageSize = 100;

		FNexusReferralAPI::FOnGetReferralInfoByPlayerIdResponse OnGetReferralInfoByPlayerIdResponse;
		OnGetReferralInfoByPlayerIdResponse.On200Response.BindUObject(this, &ULinkAccountUserWidget::OnGetReferralInfoByPlayerIdFirstCreator200ResponseComplete);
		OnGetReferralInfoByPlayerIdResponse.On400Response.BindUObject(this, &ULinkAccountUserWidget::OnGetReferralInfoByPlayerId400ResponseComplete);

		FNexusReferralAPI::GetReferralInfoByPlayerId(
			RequestParams,
			OnGetReferralInfoByPlayerIdResponse,
			FNexusOnHttpErrorDelegate::CreateUObject(this, &ULinkAccountUserWidget::OnGetReferralInfoByPlayerIdError)
		);
	}
}

void ULinkAccountUserWidget::OnGetCreatorsError(int32 ErrorCode)
{
	// #TODO display widget on screen message that get creators failed, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Failed to GetCreators. ErrorCode: %d"), ErrorCode));
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to GetCreators. ErrorCode: %d"), ErrorCode);
}

void ULinkAccountUserWidget::OnGetReferralInfoByPlayerIdFirstCreator200ResponseComplete(const FNexusReferralGetReferralInfoByPlayerId200Response& Response)
{
	if (ensureMsgf(IsValid(PlayerReferralCode), BP_ENSURE_REASON_INVALID_CLASS_WIDGET))
	{
		// #NOTE For example, we will use the 1st creator found in the GetCreators call, and assign that data to the player to mimic login
		if (Response.referralCodes.Num() > 0)
		{
			PlayerReferralCode->SetText(FText::FromString(Response.referralCodes[0].code).ToUpper());
		}
	}
}

void ULinkAccountUserWidget::OnGetReferralInfoByPlayerId400ResponseComplete(const FNexusReferralReferralError& Response)
{
	// #TODO display widget on screen message that get creator code returned 400, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("OnGetReferralInfoByPlayerId returned a 400 error with message: %s"), *Response.code));
	}

	UE_LOG(LogTemp, Error, TEXT("OnGetReferralInfoByPlayerId returned a 400 error with message: %s"), *Response.code);
}

void ULinkAccountUserWidget::OnGetReferralInfoByPlayerIdError(int32 ErrorCode)
{
	// #TODO display widget on screen message that get creator code failed, debug screen message will suffice for now
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Failed to GetCreatorCode. ErrorCode: %d"), ErrorCode));
	}

	UE_LOG(LogTemp, Error, TEXT("Failed to GetCreatorCode. ErrorCode: %d"), ErrorCode);
}