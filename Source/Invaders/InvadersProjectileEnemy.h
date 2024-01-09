// Copy Right

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvadersProjectileEnemy.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class INVADERS_API AInvadersProjectileEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	AInvadersProjectileEnemy();

protected:

	UPROPERTY(EditDefaultsOnly) TObjectPtr<UCapsuleComponent> ProjectileCollision;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ProjectileMesh;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UFUNCTION() void ProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
