// Copy Right


#include "InvadersEnemy.h"
#include "Components/BoxComponent.h"
#include "InvadersProjectile.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BrushComponent.h"

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
	NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Resources/NS_Burst"));
	BlastSound = LoadObject<USoundBase>(nullptr, TEXT("/Game/Resources/SW_Blast"));
}

// Called when the game starts or when spawned
void AInvadersEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (FTimerHandle MoveTimer; !MoveTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(MoveTimer, this, &ThisClass::Move, 0.05, true);
	}
}

void AInvadersEnemy::EnemyOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AInvadersProjectile>(OtherActor))
	{
		SpawnExplosionFX();
		SpawnSound();
		Destroy();
	}

	else if (Cast<UBrushComponent>(OtherComp))
	{
		ChangeDirection();
	}
}

void AInvadersEnemy::SpawnExplosionFX() const
{
	if (NiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, GetActorLocation());
	}
}

void AInvadersEnemy::SpawnSound() const
{
	if (BlastSound)
	{
		UGameplayStatics::PlaySound2D(this, BlastSound);
	}
}

void AInvadersEnemy::Move()
{
	const FVector NewLocation = GetActorLocation() + FVector(0.0, MoveDirection, 0.0);
	SetActorLocation(NewLocation);
}

void AInvadersEnemy::ChangeDirection()
{
	TArray <AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), StaticClass(), OutActors);
		for (AActor* EnemyActor : OutActors)
		{
			if
				(AInvadersEnemy* Enemy = Cast<AInvadersEnemy>(EnemyActor))
				{
					Enemy->MoveDirection *= -1.0;
				}
		}
}
