// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGS_Data.generated.h"

class AHGS_Settings;


/*
*	Tile Struct. Stores hex coordinates and RefCount (In case multiple objects is placed on the coordinate, this property allows keep count of them)
*/
USTRUCT(BlueprintType)
struct FHGS_Tile
{
	GENERATED_BODY()

	FHGS_Tile() : FHGS_Tile(0, 0) {}
	FHGS_Tile(int32 inQ, int32 inR) : Q(inQ), R(inR) {}
	FHGS_Tile(float inQ, float inR);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HGS | Tile")
	int32 Q;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HGS | Tile")
	int32 R;

	UPROPERTY(BlueprintReadOnly, Category = "HGS | Tile")
	int32 RefCount = 0;

	static float Distance(const FHGS_Tile& A, const FHGS_Tile& B);

	int32 GetHash();

	FORCEINLINE FString ToString() const { return FString::Printf(TEXT("Q = %d, R = %d"), Q, R); };

	FORCEINLINE FHGS_Tile operator-(const FHGS_Tile& other) const { return FHGS_Tile(Q - other.Q, R - other.R); };
	FORCEINLINE FHGS_Tile operator+(const FHGS_Tile& other) const { return FHGS_Tile(Q + other.Q, R + other.R); };
};


/*
*	Actor on level, which stores Tiles and allows to add and remove them
*	Required for actor snapping.
*	Automaticly spawns HGS_Settings, if it's not presented on the level
*/
UCLASS()
class HGS_API AHGS_Data : public AActor
{
	GENERATED_BODY()
	
public:
	AHGS_Data();

	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UFUNCTION(BlueprintCallable)
	void RemoveTileRef(FHGS_Tile& Tile);

	UFUNCTION(BlueprintCallable)
	void RemoveTileRefByKey(int32 inKey);

	UFUNCTION(BlueprintCallable)
	int32 AddTileRef(FHGS_Tile& Tile);

	UFUNCTION(BlueprintCallable)
	bool GetTileByKey(FHGS_Tile& OutTile, int32 inKey);

	UFUNCTION(BlueprintCallable)
	void GetNeighbours(TArray<FHGS_Tile>& OutArray, const FHGS_Tile& Tile) const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HGS")
	TSubclassOf<AHGS_Settings> DefaultSettingsClass;

	UPROPERTY(BlueprintReadOnly, Category = "HGS")
	TObjectPtr<AHGS_Settings> HGS_Settings;

protected:
	UPROPERTY()
	TMap<int32, FHGS_Tile> Tiles;
};
