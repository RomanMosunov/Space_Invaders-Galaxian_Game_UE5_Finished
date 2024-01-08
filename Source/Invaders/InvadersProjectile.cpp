// Copy Right


#include "InvadersProjectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "InvadersEnemy.h"

// Sets default values
AInvadersProjectile::AInvadersProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	SetLifeSpan(4.0);

	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ProjectileOverlap);
}

// Called when the game starts or when spawned
void AInvadersProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInvadersProjectile::ProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AInvadersEnemy>(OtherActor))
	{
		Destroy();
	}
}

// Called every frame
void AInvadersProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

