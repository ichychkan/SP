#include "UI/PlayerHUDWidget.h"

#include "Components/SPHealthComponent.h"
#include "Components/SPWeaponComponent.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

bool UPlayerHUDWidget::Initialize()
{
	if(IsValid(GetOwningPlayer()))
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &ThisClass::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
	return Super::Initialize();
}

float UPlayerHUDWidget::GetHealthPercent() const
{
	USPHealthComponent* HealthComponent = GetPlayerComponent<USPHealthComponent>(GetOwningPlayerPawn());
	if(IsValid(HealthComponent))
	{
		return HealthComponent->GetHealthPercent();
	}
	return 0.0f;
}

bool UPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	USPWeaponComponent* WeaponComponent = GetPlayerComponent<USPWeaponComponent>(GetOwningPlayerPawn());
	if(IsValid(WeaponComponent))
	{
		return WeaponComponent->GetWeaponUIData(UIData);
	}
	return false;
}

bool UPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
	USPWeaponComponent* WeaponComponent = GetPlayerComponent<USPWeaponComponent>(GetOwningPlayerPawn());
	if(IsValid(WeaponComponent))
	{
		return WeaponComponent->GetWeaponAmmoData(AmmoData);
	}

	return false;
}

bool UPlayerHUDWidget::IsPlayerAlive() const
{
	if(IsValid(GetOwningPlayerPawn()))
	{
		USPHealthComponent* HealthComponent = GetPlayerComponent<USPHealthComponent>(GetOwningPlayerPawn());
		return IsValid(HealthComponent) && !HealthComponent->IsDead();
	}
	return false;
}

bool UPlayerHUDWidget::IsPlayerSpectating() const
{
	AController* Controller = GetOwningPlayer();
	return IsValid(Controller) && Controller->GetStateName() == NAME_Spectating;
}

void UPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if(HealthDelta < 0)
	{
		OnTakeDamage();
	}
}

void UPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	USPHealthComponent* HealthComponent = GetPlayerComponent<USPHealthComponent>(NewPawn);
	if(IsValid(HealthComponent))
	{
		HealthComponent->GetOnHealthChanged().AddUObject(this, &ThisClass::OnHealthChanged);
	}
}
