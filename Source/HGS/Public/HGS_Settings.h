// Ullian Yunakh.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HGS_Settings.generated.h"

/*
*	Stores settings for HGS
*/
UCLASS()
class HGS_API AHGS_Settings : public AActor
{
	GENERATED_BODY()
	
public:	
	AHGS_Settings();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HGS")
	float TileSize = 50;
};
