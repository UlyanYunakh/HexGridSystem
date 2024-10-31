// Ullian Yunakh.


#include "HGS_ActorSnapComponent.h"
#include "HGS_Data.h"
#include "HGS_TileLibrary.h"

UHGS_ActorSnapComponent::UHGS_ActorSnapComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHGS_ActorSnapComponent::CreateHexTile()
{
	AActor* Owner = GetOwner();
	check(Owner);

	AHGS_Data* HGS = UHGS_Library::GetHGS(GetWorld());
	if (!HGS)
	{
		UE_LOG(LogTemp, Warning, TEXT("No HGS on level, snapping is disabled."));
		return;
	}

	FHGS_Tile Tile = UHGS_Library::WorldSpaceToHex(HGS, Owner->GetActorLocation());
	TileKey = HGS->AddTileRef(Tile);

	FVector SnappedLocation = UHGS_Library::HexToWorldSpace(HGS, Tile); // for snapping
	SetWorldLocation(SnappedLocation);
}

void UHGS_ActorSnapComponent::RemoveHexTile()
{
	AHGS_Data* HGS = UHGS_Library::GetHGS(GetWorld());
	if (HGS)
	{
		HGS->RemoveTileRefByKey(TileKey);
	}
}

#if WITH_EDITOR
void UHGS_ActorSnapComponent::OnRegister()
{
	Super::OnRegister();

	CreateHexTile();
}
void UHGS_ActorSnapComponent::OnUnregister()
{
	Super::OnUnregister();

	RemoveHexTile();
}
#endif

