#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SaveMyselfPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

struct FInputActionValue;

UCLASS()
class DEFENSE_SAVEMYSELF_API ASaveMyselfPlayerController : public APlayerController
{
	GENERATED_BODY()

public :
	ASaveMyselfPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected :
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private :
	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess="true"))
	TObjectPtr<UInputMappingContext> SaveMyselfContext;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookNTurnAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PauseAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot01;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot02;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot03;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot04;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot05;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot06;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot07;

	UPROPERTY(EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuickSlot08;

	void Move(const FInputActionValue& InputActionValue);
	void LookNTurn(const FInputActionValue& InputActionValue);
	void ViewPause();
	void Interaction();
};
