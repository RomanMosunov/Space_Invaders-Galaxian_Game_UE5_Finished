// Copy Right

#include "InvadersProjectileEnemy.h"
#include "InvadersProjectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "InvadersShip.h"
#include "Components/BrushComponent.h"

AInvadersProjectileEnemy::AInvadersProjectileEnemy()
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
	ProjectileMesh->SetRelativeRotation(FRotator(180.0, 0.0, 0.0));
	SetLifeSpan(2.0);

	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ProjectileOverlap);
}

void AInvadersProjectileEnemy::ProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AInvadersShip>(OtherActor) || Cast<UBrushComponent>(OtherComp))
	{
		Destroy();
	}
}
