// Copy Right

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InvadersWall.generated.h"

UCLASS()
class INVADERS_API AInvadersWall : public AActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	void ConstructWall();
	UFUNCTION() void WallOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
