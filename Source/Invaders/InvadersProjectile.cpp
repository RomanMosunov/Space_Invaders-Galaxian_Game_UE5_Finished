// Copy Right

#include "InvadersProjectile.h"
#include "InvadersEnemy.h"
#include "InvadersWall.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BrushComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AInvadersProjectile::AInvadersProjectile()
{
	ProjectileCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ProjectileCollision"));
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

	check(ProjectileCollision);
	check(ProjectileMesh);
	check(ProjectileMovement);

	SetRootComponent(ProjectileCollision);
	ProjectileMesh->SetupAttachment(ProjectileCollision);
	ProjectileCollision->SetCapsuleHalfHeight(30.0);
	ProjectileCollision->SetCapsuleRadius(20.0);
	ProjectileMesh->SetRelativeScale3D(FVector(0.4, 0.4, 0.6));
	SetLifeSpan(2.0);

	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ProjectileOverlap);
}

void AInvadersProjectile::ProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AInvadersEnemy>(OtherActor) || Cast<UBrushComponent>(OtherComp) || (Cast<AInvadersWall>(OtherActor)))
	{
		if(FTimerHandle Delay; !Delay.IsValid())
		{
			GetWorldTimerManager().SetTimer(Delay, this, &ThisClass::DelayedDestroy, 0.02, false);
		}
	}
}

void AInvadersProjectile::DelayedDestroy()
{
		Destroy();
}
