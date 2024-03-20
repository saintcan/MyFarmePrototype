#include "ManPickup.h"
#include "MyFarmePrototypePlayerController.h"

AManPickup::AManPickup()
{
    PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
    RootComponent = Cast<UStaticMeshComponent>(PickupMesh);

    ItemID = FName("No ID");

    Super::Name = "Item";
    Super::Action = "pickup";
}

void AManPickup::Interact_Implementation(APlayerController* Controller)
{
    Super::Interact_Implementation(Controller);

    AMyFarmePrototypePlayerController* IController = Cast<AMyFarmePrototypePlayerController>(Controller);
    if (IController->AddItemToInventoryByID(ItemID))
        Destroy();
}