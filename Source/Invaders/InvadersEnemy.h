// Copy Right

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvadersEnemy.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UNiagaraSystem;

UCLASS()
class INVADERS_API AInvadersEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInvadersEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly) TObjectPtr<UBoxComponent> EnemyCollision;
	UPROPERTY(EditDefaultsOnly) TObjectPtr <UStaticMeshComponent> EnemyMesh;
	UPROPERTY() TObjectPtr <UNiagaraSystem> NiagaraSystem;
	UPROPERTY() TObjectPtr <USoundBase> BlastSound;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor> ActorToSpawn;
	
	FTimerHandle ReloadTimerHandle;
	double MoveDirection = -1.0;
	int32 ProjectilesCount;
	const int32 ProjectilesMax = 5;

	UFUNCTION() void EnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void SpawnExplosionFX() const;
	void SpawnSound() const;
	void Move();
	void ChangeDirection() const;
	void BeginFire();
	void SpawnProjectile();
	void ProjectileCheck();
};
