// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "UI/PauseMenuUserWidget.h"
#include "UI/CreatorSupportUserWidget.h"
#include "UI/BountiesUserWidget.h"
#include "UI/ReferralsBountiesMenuUserWidget.h"
#include "NexusSampleProjectCharacter.generated.h"

UCLASS(Blueprintable)
class ANexusSampleProjectCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANexusSampleProjectCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;

	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputAction> PauseAction;

	UPROPERTY(EditAnywhere, Category = "Menu Class Types")
	TSubclassOf<UPauseMenuUserWidget> PauseMenuWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UPauseMenuUserWidget* PauseMenuWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UReferralsBountiesMenuUserWidget* ReferralsBountiesMenuWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UCreatorSupportUserWidget* CreatorSupportWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	ULinkAccountUserWidget* LinkAccountWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UBountiesUserWidget* BountiesWidget;
	
	UPROPERTY(BlueprintReadOnly, Category = "Menus")
	UItemShopMenuUserWidget* ItemShopMenuWidget;

protected:
	// ~APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// ~End APawn interface

	void Pause(const FInputActionInstance& Instance);

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};

