#include "Player/SaveMyselfPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ASaveMyselfPlayerController::ASaveMyselfPlayerController()
{
	
}

void ASaveMyselfPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void ASaveMyselfPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(SaveMyselfContext)

	auto* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(SaveMyselfContext, 0);
	}

}

void ASaveMyselfPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASaveMyselfPlayerController::Move);
	EnhancedInputComponent->BindAction(LookNTurnAction, ETriggerEvent::Triggered, this, &ASaveMyselfPlayerController::LookNTurn);
	EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::ViewPause);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ASaveMyselfPlayerController::Interaction);

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
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf("ViewPause"));
}

void ASaveMyselfPlayerController::Interaction()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, FString::Printf("Interaction"));
}

