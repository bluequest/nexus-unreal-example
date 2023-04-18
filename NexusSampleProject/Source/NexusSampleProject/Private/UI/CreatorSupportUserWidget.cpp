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

	if (ensure(IsValid(BackButton)))
	{
		GameAndUIMode.SetWidgetToFocus(BackButton->TakeWidget());
	}

	Controller->SetInputMode(GameAndUIMode);
}

void UCreatorSupportUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ensure(IsValid(BackButton)))
	{
		BackButton->OnClicked.AddDynamic(this, &UCreatorSupportUserWidget::OnBackButtonPressed);
	}

	if (ensure(IsValid(SubmitButton)))
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
	if (ensure(IsValid(CreatorCodeInputTextBox)))
	{
		if (CreatorCodeInputTextBox->GetText().IsEmpty()) 
		{
			return;
		}

		// #TODO Remove me! Just used for testing cat facts API
		OnGetGatFactsCompleteDelegate.BindUObject(this, &UCreatorSupportUserWidget::OnGetCatFactsComplete);
		NexusSDK::FGetCatFactsRequest GetCatFactsRequest;
		GetCatFactsRequest.MaxLength = 32;
		GetCatFactsRequest.Limit = 32;
		NexusSDK::GetCatFacts(GetCatFactsRequest, OnGetGatFactsCompleteDelegate);

		// #TODO save the code on disk, then on purchase (transactions page), reference this code and call the create new sale attributed to a creator endpoint (https://api.nexus.gg/v1/attributions/transactions)
	
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Creator Code saved to settings!")));
		}

		CreatorCodeInputTextBox->SetText(FText());
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