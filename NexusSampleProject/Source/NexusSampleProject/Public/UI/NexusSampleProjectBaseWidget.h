// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NexusSampleProject/Public/NexusSampleProjectGlobals.h"
#include "NexusSampleProjectBaseWidget.generated.h"

/**
 *  Widget base class to derive from for this sample project
 */
UCLASS()
class NEXUSSAMPLEPROJECT_API UNexusSampleProjectBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/**
	 * Used to setup initial focus and input mode
	 *
	 * @param Controller the APlayerController instance to set focus
	 */
	virtual void SetupInitialFocus(APlayerController* Controller);

protected:

	void NativeConstruct() override;
	
};
