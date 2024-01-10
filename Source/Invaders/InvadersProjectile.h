// Copy Right

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvadersProjectile.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class INVADERS_API AInvadersProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AInvadersProjectile();

protected:

	UPROPERTY(EditDefaultsOnly) TObjectPtr<UCapsuleComponent> ProjectileCollision;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UFUNCTION() void ProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void DelayedDestroy();
};
