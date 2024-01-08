// Copy Right


#include "InvadersEnemy.h"
#include "Components/BoxComponent.h"
#include "InvadersProjectile.h"

// Sets default values
AInvadersEnemy::AInvadersEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyCollision"));
	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));

	check(EnemyCollision);
	check(EnemyMesh);

	SetRootComponent(EnemyCollision);
	EnemyMesh->SetupAttachment(EnemyCollision);
	EnemyCollision->SetBoxExtent(FVector(51.0, 51.0, 51.0));
	EnemyCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::EnemyOverlap);
}

// Called when the game starts or when spawned
void AInvadersEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInvadersEnemy::EnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AInvadersProjectile>(OtherActor))
	{
		Destroy();
	}
}

// Called every frame
void AInvadersEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

