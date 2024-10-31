// Ullian Yunakh.


#include "HGS_TileLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "HGS_Data.h"
#include "HGS_Settings.h"

AHGS_Data* UHGS_Library::GetHGS(UObject* Context)
{
	UWorld* World = Context->GetWorld();
	checkf(World, TEXT("Contex is null"));

	AActor* Actor = UGameplayStatics::GetActorOfClass(Context, AHGS_Data::StaticClass());
	if (AHGS_Data* HGS = Cast<AHGS_Data>(Actor))
	{
		return HGS;
	}

	return nullptr;
}

FHGS_Tile UHGS_Library::WorldSpaceToHex(AHGS_Data* Context, const FVector& WorldSpace)
{
	float Size = Context->HGS_Settings->TileSize;
	float Q = (FMath::Sqrt(3.f) / 3 * WorldSpace.X - 1.f / 3 * WorldSpace.Y) / Size;
	float R = (2.f / 3 * WorldSpace.Y) / Size;

	return FHGS_Tile(Q, R);
}

FVector UHGS_Library::HexToWorldSpace(AHGS_Data* Context, const FHGS_Tile& Hex)
{
	float Size = Context->HGS_Settings->TileSize;
	float X = Size * (FMath::Sqrt(3.f) * Hex.Q + (FMath::Sqrt(3.f) / 2) * Hex.R);
	float Y = Size * (3.f / 2 * Hex.R);

	return FVector(X, Y, 0);
}

FString UHGS_Library::TileToSring(const FHGS_Tile& Tile)
{
	return Tile.ToString();
}

float UHGS_Library::TileDistance(const FHGS_Tile& A, const FHGS_Tile& B)
{
	return FHGS_Tile::Distance(A, B);
}
