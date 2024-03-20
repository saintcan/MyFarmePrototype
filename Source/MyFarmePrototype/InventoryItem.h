#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "InventoryItem.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
    Common UMETA(DisplayName = "Common"),
    Uncommon UMETA(DisplayName = "Uncommon"),
    Rare UMETA(DisplayName = "Rare"),
    Epic UMETA(DisplayName = "Epic"),
    Legendary UMETA(DisplayName = "Legendary")
};

UENUM(BlueprintType)
enum class EItemLevel : uint8
{
    Level1 UMETA(DisplayName = "Level 1"),
    Level2 UMETA(DisplayName = "Level 2"),
    Level3 UMETA(DisplayName = "Level 3"),
    Level4 UMETA(DisplayName = "Level 4"),
    Level5 UMETA(DisplayName = "Level 5")
};

USTRUCT(BlueprintType)
struct FInventoryItem : public FTableRowBase
{
    GENERATED_BODY()

public:
    FInventoryItem();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName ItemID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Weight;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Value;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Thumbnail;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemRarity Rarity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EItemLevel Level;

    bool operator==(const FInventoryItem& OtherItem) const
    {
        if (ItemID == OtherItem.ItemID)
            return true;
        return false;
    }
};
