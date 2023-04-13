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

	// #TODO Add SDK call
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, FString::Printf(TEXT("Creator Code Submitted!")));
	}
}
