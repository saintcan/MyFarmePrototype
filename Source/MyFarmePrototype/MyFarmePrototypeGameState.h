#pragma once

#include "Engine.h"
#include "GameFramework/GameStateBase.h"
#include "MyFarmePrototypeGameState.generated.h"

UCLASS()
class MYFARMEPROTOTYPE_API AMyFarmePrototypeGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    AMyFarmePrototypeGameState();

    UDataTable* GetItemDB() const;

protected:
    UPROPERTY(EditDefaultsOnly)
    class UDataTable* ItemDB;
};
