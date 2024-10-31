// Ullian Yunakh.


#include "HGS_Data.h"
#include "Kismet/GameplayStatics.h"
#include "HGS_Settings.h"

/* Start of FHGS_Tile */
FHGS_Tile::FHGS_Tile(float inQ, float inR) // Round to int32
{
	float S = -inQ - inR;

	int32 newQ = FMath::RoundToInt32(inQ);
	int32 newR = FMath::RoundToInt32(inR);
	int32 newS = FMath::RoundToInt32(S);

	float QDiff = FMath::Abs(newQ - inQ);
	float RDiff = FMath::Abs(newR - inR);
	float SDiff = FMath::Abs(newS - S);

	if (QDiff > RDiff && QDiff > SDiff)
	{
		newQ = -newR - newS;
	}
	else if (RDiff > SDiff)
	{
		newR = -newQ - newS;
	}

	Q = newQ;
	R = newR;
}

float FHGS_Tile::Distance(const FHGS_Tile& A, const FHGS_Tile& B)
{
	FHGS_Tile Vector = A - B;
	return 0.5f * (FMath::Abs(Vector.Q) + FMath::Abs(Vector.Q + Vector.R) + FMath::Abs(Vector.R));
}

int32 FHGS_Tile::GetHash()
{
	std::hash<int32> hash_int;
	size_t hq = hash_int(Q);
	size_t hr = hash_int(R);

	return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2));
}
/* End of FHGS_Tile */


/* Start of AHGS_Data*/
AHGS_Data::AHGS_Data()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultSettingsClass = AHGS_Settings::StaticClass();
}

void AHGS_Data::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	checkf(DefaultSettingsClass, TEXT("Default HGS settings class is null"));

	if (UWorld* World = GetWorld())
	{
		AActor* Actor = UGameplayStatics::GetActorOfClass(World, DefaultSettingsClass);
		if (!Actor)
		{
			Actor = World->SpawnActor(DefaultSettingsClass); // spawn settings if not found;
			checkf(Actor, TEXT("Failed to spawn HGS settings"));
		}

		HGS_Settings = Cast<AHGS_Settings>(Actor);
	}

	Tiles.Empty();
}

void AHGS_Data::RemoveTileRef(FHGS_Tile& Tile)
{
	int32 Key = Tile.GetHash();

	return RemoveTileRefByKey(Key);
}

void AHGS_Data::RemoveTileRefByKey(int32 inKey)
{
	if (Tiles.Contains(inKey))
	{
		Tiles[inKey].RefCount--;
		if (Tiles[inKey].RefCount == 0)
		{
			Tiles.Remove(inKey);
		}
	}
}

int32 AHGS_Data::AddTileRef(FHGS_Tile& Tile)
{
	int32 Key = Tile.GetHash();

	if (!Tiles.Contains(Key))
	{
		Tiles.Add(Key, Tile);
		Tiles[Key].RefCount++;
	}
	else
	{
		Tiles[Key].RefCount++;
	}

	return Key;
}

bool AHGS_Data::GetTileByKey(FHGS_Tile& OutTile, int32 inKey)
{
	if (Tiles.Contains(inKey))
	{
		OutTile = Tiles[inKey];
		return true;
	}

	return false;
}

void AHGS_Data::GetNeighbours(TArray<FHGS_Tile>& OutArray, const FHGS_Tile& Tile) const
{
	if (!OutArray.IsEmpty())
	{
		OutArray.Empty();
	}

	static FHGS_Tile Directions[] = { FHGS_Tile(1, 0), FHGS_Tile(1, -1), FHGS_Tile(0, -1), FHGS_Tile(-1, 0), FHGS_Tile(-1, 1), FHGS_Tile(0, 1) };

	for (const FHGS_Tile& direction : Directions)
	{
		FHGS_Tile PotentialNeighbour = Tile + direction;
		int32 PotentialNeighbourKey = PotentialNeighbour.GetHash();

		if (Tiles.Contains(PotentialNeighbourKey))
		{
			OutArray.Add(Tiles[PotentialNeighbourKey]);
		}
	}
}
/* End of AHGS_Data */
