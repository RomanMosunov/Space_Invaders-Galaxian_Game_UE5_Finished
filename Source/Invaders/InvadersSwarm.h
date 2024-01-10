// Copy Right

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvadersSwarm.generated.h"

UCLASS()
class INVADERS_API AInvadersSwarm : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor> ActorToSpawn;
	int32 EnemyCount;
	void SpawnEnemies() const;
	void CheckEnemies();
};
