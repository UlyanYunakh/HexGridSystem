// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "HGS_TileLibrary.generated.h"

class AHGS_Data;
struct FHGS_Tile;

/**
 * Helper library, exposes some function to BP
 */
UCLASS()
class HGS_API UHGS_Library : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "HGS")
	static AHGS_Data* GetHGS(UObject* Context);

	UFUNCTION(BlueprintCallable, Category = "HGS")
	static FHGS_Tile WorldSpaceToHex(AHGS_Data* Context, const FVector& WorldSpace);

	UFUNCTION(BlueprintCallable, Category = "HGS")
	static FVector HexToWorldSpace(AHGS_Data* Context, const FHGS_Tile& Hex);

	UFUNCTION(BlueprintPure, Category = "HGS")
	static FString TileToSring(const FHGS_Tile& Tile);

	UFUNCTION(BlueprintPure, Category = "HGS")
	static float TileDistance(const FHGS_Tile& A, const FHGS_Tile& B);
};
