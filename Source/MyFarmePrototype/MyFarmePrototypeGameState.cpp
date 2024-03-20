#include "MyFarmePrototypeGameState.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

AMyFarmePrototypeGameState::AMyFarmePrototypeGameState()
{
    static ConstructorHelpers::FObjectFinder<UDataTable> BP_ItemDB(TEXT("DataTable'/Game/Data/ItemDB.ItemDB'"));
    if (BP_ItemDB.Succeeded())
    {
        ItemDB = BP_ItemDB.Object;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to load ItemDB DataTable."));
    }
}

UDataTable* AMyFarmePrototypeGameState::GetItemDB() const
{
    return ItemDB;
}
