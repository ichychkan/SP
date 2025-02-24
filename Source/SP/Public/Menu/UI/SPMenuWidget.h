#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UI/SPGoToButtonWidget.h"
#include "Components/EditableTextBox.h"
#include "SPMenuWidget.generated.h"

UCLASS()
class SP_API USPMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnExitButtonPressed();

	UFUNCTION()
	void OnStartGameButtonPressed();

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	UFUNCTION()
	void OnTextChanged(const FText& Text);
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USPGoToButtonWidget> StartGameButton;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UEditableTextBox> PlayerCountEditableTextBox;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> HideAnimation;
};
