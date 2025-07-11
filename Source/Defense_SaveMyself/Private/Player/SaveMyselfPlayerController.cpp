#include "Player/SaveMyselfPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/ActorSpawnComponent.h"
#include "Game/Subsystem/SaveMyselfItemSubsystem.h"

ASaveMyselfPlayerController::ASaveMyselfPlayerController()
{
	
}

void ASaveMyselfPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(SaveMyselfContext)

	if (auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (Subsystem)
		{
			Subsystem->AddMappingContext(SaveMyselfContext, 0);
		}
	}

	if (USaveMyselfItemSubsystem* ItemSubsystem = GetGameInstance()->GetSubsystem<USaveMyselfItemSubsystem>())
	{
		this->ExportQuickSlotIndexDelegate.AddDynamic(ItemSubsystem, &USaveMyselfItemSubsystem::GetQuickSlotIndexItemData);

		if (APawn* PlayerPawn = GetPawn())
		{
			if (UActorSpawnComponent* SpawnComp = PlayerPawn->FindComponentByClass<UActorSpawnComponent>())
			{
				ItemSubsystem->RegisterSpawnComponent(SpawnComp);
			}
		}
	}
}

void ASaveMyselfPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASaveMyselfPlayerController::Move);
	EnhancedInputComponent->BindAction(LookNTurnAction, ETriggerEvent::Triggered, this, &ASaveMyselfPlayerController::LookNTurn);
	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::ViewPause);
	EnhancedInputComponent->BindAction(ConfirmAction, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::Confirm);

	EnhancedInputComponent->BindAction(QuickSlot01, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::SetQuickSlot1);
	EnhancedInputComponent->BindAction(QuickSlot02, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::SetQuickSlot2);
	EnhancedInputComponent->BindAction(QuickSlot03, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::SetQuickSlot3);
	EnhancedInputComponent->BindAction(QuickSlot04, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::SetQuickSlot4);
	EnhancedInputComponent->BindAction(QuickSlot05, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::SetQuickSlot5);
	EnhancedInputComponent->BindAction(QuickSlot06, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::SetQuickSlot6);
	EnhancedInputComponent->BindAction(QuickSlot07, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::SetQuickSlot7);
	EnhancedInputComponent->BindAction(QuickSlot08, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::SetQuickSlot8);

}

void ASaveMyselfPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ASaveMyselfPlayerController::LookNTurn(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerYawInput(LookAxisVector.X * 0.5);
	}
}

void ASaveMyselfPlayerController::ViewPause()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf(TEXT("ViewPause")));
}

void ASaveMyselfPlayerController::Confirm()
{
	ItemConfirmActionDelegate.Broadcast();
}

void ASaveMyselfPlayerController::SetQuickSlot1()
{
	ExportQuickSlotIndexDelegate.Broadcast(0);
}

void ASaveMyselfPlayerController::SetQuickSlot2()
{
	ExportQuickSlotIndexDelegate.Broadcast(1);
}

void ASaveMyselfPlayerController::SetQuickSlot3()
{
	ExportQuickSlotIndexDelegate.Broadcast(2);
}

void ASaveMyselfPlayerController::SetQuickSlot4()
{
	ExportQuickSlotIndexDelegate.Broadcast(3);
}

void ASaveMyselfPlayerController::SetQuickSlot5()
{
	ExportQuickSlotIndexDelegate.Broadcast(4);
}

void ASaveMyselfPlayerController::SetQuickSlot6()
{
	ExportQuickSlotIndexDelegate.Broadcast(5);
}

void ASaveMyselfPlayerController::SetQuickSlot7()
{
	ExportQuickSlotIndexDelegate.Broadcast(6);
}

void ASaveMyselfPlayerController::SetQuickSlot8()
{
	ExportQuickSlotIndexDelegate.Broadcast(7);
}


