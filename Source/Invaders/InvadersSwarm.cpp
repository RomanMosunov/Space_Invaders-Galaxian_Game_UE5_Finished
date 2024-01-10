// Copy Right

#include "InvadersSwarm.h"
#include "InvadersEnemy.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void AInvadersSwarm::BeginPlay()
{
	Super::BeginPlay();
	SpawnEnemies();
	FTimerHandle CheckEnemiesTimer;
	if (!CheckEnemiesTimer.IsValid())
	{
		GetWorldTimerManager().SetTimer(CheckEnemiesTimer, this, &AInvadersSwarm::CheckEnemies, 2.0, true);
	}
}

void AInvadersSwarm::SpawnEnemies() const
{
	const FVector SpawnLocation = GetActorLocation();
	double Spacing = 120.0;
	const int32 CountY = 20;
	const int32 CountZ = 5;

	for (int32 j = 0; j < CountZ; j++)
	{
		for (int32 i = 0; i < CountY; i++)
		{
			if (UWorld* World = GetWorld())
			{
				World->SpawnActor<AActor>(ActorToSpawn, (SpawnLocation + FVector(0.0, i * Spacing, j * Spacing)), FRotator::ZeroRotator);
			}
		}
	}
}

void AInvadersSwarm::CheckEnemies()
{
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AInvadersEnemy::StaticClass(), OutActors);
		TArray<AInvadersEnemy*> EnemyArray;
		for (AActor* Actor : OutActors)
		{
			if (AInvadersEnemy* Enemy = Cast<AInvadersEnemy>(Actor))
			{
				EnemyArray.Add(Enemy);
			}
		}
		EnemyCount = EnemyArray.Num();
	UE_LOG(LogTemp, Warning, TEXT("actors: %d"), EnemyCount);
	if (EnemyCount <= 0)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}
