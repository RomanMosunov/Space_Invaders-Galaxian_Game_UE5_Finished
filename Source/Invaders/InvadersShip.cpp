#include "InvadersShip.h"
#include "InvadersPlayerController.h"
#include "InvadersProjectileEnemy.h"
#include "Components/SphereComponent.h"
#include "Components/StaticmeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

AInvadersShip::AInvadersShip()
{
	ShipCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ShipCollision"));
	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("ShipMovement"));

	check(ShipCollision);
	check(ShipMesh);
	check(ShipMovement);

	SetRootComponent(ShipCollision);
	ShipCollision->SetSphereRadius(50.0);
	ShipMesh->SetupAttachment(ShipCollision);
	ShipCollision->SetCollisionProfileName(TEXT("Pawn"));
	ShipCollision->OnComponentBeginOverlap.AddDynamic(this, &AInvadersShip::ShipOverlap);
	NiagaraSystem = LoadObject<UNiagaraSystem>(nullptr, TEXT("/Game/Resources/NS_Trace"));
}

// Called when the game starts or when spawned
void AInvadersShip::BeginPlay()
{
	Super::BeginPlay();
	
	const AInvadersPlayerController* PlayerController = Cast<AInvadersPlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}
}

void AInvadersShip::Move(const FInputActionValue& Value)
{
	const float FloatValue = Value.Get<float>();
	const FVector RightVector = GetActorRightVector();
	AddMovementInput(RightVector, FloatValue);
	SpawnTrace();
}

void AInvadersShip::Fire(const FInputActionValue& Value)
{
	if(CanShoot)
	{
		CanShoot = false;
		SpawnActor();
		GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AInvadersShip::Reload, ReloadTime, false);
	}
}

void AInvadersShip::Reload()
{
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);
	CanShoot = true;
}

void AInvadersShip::SpawnActor()
{
	const FVector SpawnLoc = GetActorLocation() + FVector(0.0, 0.0, 100.0);
	if (UWorld* World = GetWorld())
	{
		World->SpawnActor<AActor>(ActorToSpawn, SpawnLoc, FRotator::ZeroRotator);
	}
}

void AInvadersShip::RestartLevel()
{
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AInvadersShip::SpawnTrace() const
{
	if (NiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraSystem, GetActorLocation());
	}
}

void AInvadersShip::ShipOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AInvadersProjectileEnemy>(OtherActor)) {
		ShipMesh->SetVisibility(false);
		RestartLevel();
	}
}

// Called to bind functionality to input
void AInvadersShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AInvadersShip::Move);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AInvadersShip::Fire);
	}
}
