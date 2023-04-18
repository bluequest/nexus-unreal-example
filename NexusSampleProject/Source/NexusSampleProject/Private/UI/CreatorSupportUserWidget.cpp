// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CreatorSupportUserWidget.h"
#include "NexusSampleProject/NexusSampleProject.h"
#include "NexusSampleProject/NexusSampleProjectCharacter.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
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

	// #TODO Remove me! Just used for testing cat facts API
	OnGetGatFactsCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnGetCatFactsComplete);
	NexusSDK::FGetCatFactsRequest GetCatFactsRequest;
	GetCatFactsRequest.MaxLength = 32;
	GetCatFactsRequest.Limit = 32;
	NexusSDK::GetCatFacts(GetCatFactsRequest, OnGetGatFactsCompleteDelegate);

	// #TODO Replace SDK call with https://docs.nexus.gg/reference/rest-api/api-reference/referrals/create

	// #TODO Replace logic when Unreal SDK template is in.
	//OnSubmitReferralCodeCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnSubmitReferralCodeComplete);
	//NexusSDK::SubmitReferralCode(32, 32, OnSubmitReferralCodeCompleteDelegate);
	
	// #TODO Replace logic below when NexusSDK::SubmitReferralCode is in
	//FString TestGroupId = TEXT("TestGroupId");
	//FString TestGroupName = TEXT("TestGroupName");
	//OnSubmitReferralCodeComplete(TestGroupId, TestGroupName, true);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Creator Code Submitted!")));
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
		UE_LOG(LogNexusSampleProject, Warning, TEXT("Get cat facts failed!"));
	}
}	

void UCreatorSupportUserWidget::OnSubmitReferralCodeComplete(FString& GroupId, FString& GroupName, /* FReferralStruct ReferralInfo, */ bool bWasSuccessful)
{
	if (bWasSuccessful && !GroupId.IsEmpty() && !GroupName.IsEmpty()) 
	{
		// Logging
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Submit creator (referral) code success! Response - GroupId: %s, GroupName: %s"), *GroupId, *GroupName));
		}

		UE_LOG(LogNexusSampleProject, Log, TEXT("Submit creator (referral) code succeeded! Response - GroupId: %s, GroupName : %s"), *GroupId, *GroupName);
	}
	else 
	{
		UE_LOG(LogNexusSampleProject, Warning, TEXT("Submit creator (referral) code failed!"));
	}	
}