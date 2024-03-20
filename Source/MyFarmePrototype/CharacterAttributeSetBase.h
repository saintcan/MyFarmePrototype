#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CharacterAttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
    GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class MYFARMEPROTOTYPE_API UCharacterAttributeSetBase : public UAttributeSet
{
    GENERATED_BODY()

public:
    UCharacterAttributeSetBase();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    FGameplayAttributeData Health;
    ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Health)

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina")
    FGameplayAttributeData Stamina;
    ATTRIBUTE_ACCESSORS(UCharacterAttributeSetBase, Stamina)
};
