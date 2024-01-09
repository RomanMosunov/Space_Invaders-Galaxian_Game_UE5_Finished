// Copy Right

#include "InvadersProjectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "InvadersEnemy.h"
#include "Components/BrushComponent.h"

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
	if (Cast<AInvadersEnemy>(OtherActor) || Cast<UBrushComponent>(OtherComp))
	{
		Destroy();
	}
}
