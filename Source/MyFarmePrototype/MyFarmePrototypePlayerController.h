#pragma once

#include "CoreMinimal.h"
#include "InventoryItem.h"
#include "Interactable.h"
#include "Templates/SubclassOf.h"
#include "GameFramework/PlayerController.h"
#include "MyFarmePrototypePlayerController.generated.h"

/** Forward declaration to improve compiling times */
class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
class AMyFarmePrototypePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyFarmePrototypePlayerController();

	UFUNCTION(BlueprintImplementableEvent)
	void ReloadInventory();

	UFUNCTION(BlueprintCallable, Category = "Utils")
	int32 GetInventoryWeight();

	UFUNCTION(BlueprintCallable, Category = "Utils")
	bool AddItemToInventoryByID(FName ID);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	AInteractable* CurrentInteractable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FInventoryItem> Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int32 Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InventorySlotLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InventoryWeightLimit;

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationClickAction;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SetDestinationTouchAction;

protected:
	void Interact();

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnTouchTriggered();
	void OnTouchReleased();

private:
	FVector CachedDestination;

	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};
