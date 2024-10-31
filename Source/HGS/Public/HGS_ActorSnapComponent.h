// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "HGS_ActorSnapComponent.generated.h"

/*
* This component snappes scene to HexGrid.
* THIS COMPONENT CANNOT BE A ROOT COMPONENT OF AN ACTOR. 
* 
* This Class also stores a Key, by which user can access HexTile struct.
* 
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HGS_API UHGS_ActorSnapComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UHGS_ActorSnapComponent();

	void CreateHexTile();

	void RemoveHexTile();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "HGS | Tile", meta=(AllowPrivateAccess = true))
	int32 TileKey;

#if WITH_EDITOR
public:
	virtual void OnRegister() override; // overiiding only in editor, because in shipment build all hexes should be alredy in correct place

	virtual void OnUnregister() override;
#endif
};
