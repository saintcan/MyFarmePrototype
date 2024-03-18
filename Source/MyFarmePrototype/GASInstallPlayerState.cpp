#include "GASInstallPlayerState.h"
#include "AbilitySystemComponent.h"

AGASInstallPlayerState::AGASInstallPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
}