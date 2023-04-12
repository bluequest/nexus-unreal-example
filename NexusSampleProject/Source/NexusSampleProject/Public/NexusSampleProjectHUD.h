// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "NexusSampleProjectHUD.generated.h"

class UHUDUserWidget;

UCLASS()
class NEXUSSAMPLEPROJECT_API ANexusSampleProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UHUDUserWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UHUDUserWidget* HUDWidget;

protected:
	void BeginPlay() override;
	
};
