// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CreatorSupportUserWidget.h"
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
	//OnGetGatFactsCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnGetCatFactsComplete);
	//NexusSDK::GetCatFacts(32, 32, OnGetGatFactsCompleteDelegate);

	// #TODO Replace SDK call with https://docs.nexus.gg/reference/rest-api/api-reference/referrals/create

	// #TODO Replace logic when Unreal SDK template is in.
	//OnSubmitReferralCodeCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnSubmitReferralCodeComplete);
	//NexusSDK::SubmitReferralCode(32, 32, OnSubmitReferralCodeCompleteDelegate);
	
	// #TODO Replace logic below when NexusSDK::SubmitReferralCode is in
	FString TestGroupId = TEXT("TestGroupId");
	FString TestGroupName = TEXT("TestGroupName");
	OnSubmitReferralCodeComplete(TestGroupId, TestGroupName, true);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Creator Code Submitted!")));
	}
}

// #TODO Remove me! Just used for testing cat facts API
void UCreatorSupportUserWidget::OnGetCatFactsComplete(TArray<FString>& FatFactsArray, bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Get cat facts successful!")));
		}
	}
}

void UCreatorSupportUserWidget::OnSubmitReferralCodeComplete(FString& GroupId, FString& GroupName, /* FReferralStruct ReferralInfo, */ bool bWasSuccessful)
{
	if (bWasSuccessful && !GroupId.IsEmpty() && !GroupName.IsEmpty()) 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Submit creator (referral) code success! Response - GroupId: %s, GroupName: %s"), *GroupId, *GroupName));
		}
	}
}
