#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SaveMyselfPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FExportQuickSlotIndexDelegate, const int32, Index /** Use QuickSlot Index*/);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemConfirmActionDelegate);

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfPlayerController : public APlayerController
{
	GENERATED_BODY()

public :
	ASaveMyselfPlayerController();

	UPROPERTY(BlueprintAssignable)
	FExportQuickSlotIndexDelegate ExportQuickSlotIndexDelegate;

	FItemConfirmActionDelegate ItemConfirmActionDelegate;

protected :
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private :
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> SaveMyselfContext;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;
	void Move(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookNTurnAction;
	void LookNTurn(const FInputActionValue& InputActionValue);

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;
	void ViewPause();

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ConfirmAction;
	void Confirm();
	 
	// SetQuickSlot1 = PlayerQuickSlotData[0]
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot01;
	void SetQuickSlot1();

	// SetQuickSlot2 = PlayerQuickSlotData[1]
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot02;
	void SetQuickSlot2();

	// SetQuickSlot3 = PlayerQuickSlotData[2]
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot03;
	void SetQuickSlot3();

	// SetQuickSlot4 = PlayerQuickSlotData[3]
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot04;
	void SetQuickSlot4();

	// SetQuickSlot5 = PlayerQuickSlotData[4]
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot05;
	void SetQuickSlot5();

	// SetQuickSlot6 = PlayerQuickSlotData[5]
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot06;
	void SetQuickSlot6();

	// SetQuickSlot7 = PlayerQuickSlotData[6]
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot07;
	void SetQuickSlot7();

	// SetQuickSlot8 = PlayerQuickSlotData[7]
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot08;
	void SetQuickSlot8();
};
