// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "InvadersShip.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UFloatingPawnMovement;
class UInputMappingContext;
struct FInputActionValue;
class UInputAction;

UCLASS()
class INVADERS_API AInvadersShip : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInvadersShip();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly) TObjectPtr<USphereComponent> ShipCollision;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UStaticMeshComponent> ShipMesh;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UFloatingPawnMovement> ShipMovement;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UInputMappingContext> InputMapping;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UInputAction>MoveAction;
	UPROPERTY(EditDefaultsOnly) TObjectPtr<UInputAction>FireAction;
	UPROPERTY(EditDefaultsOnly) TSubclassOf<AActor>ActorToSpawn;

	FTimerHandle ReloadTimerHandle;
	bool CanShoot = true;
	float ReloadTime = 0.5;

	void Move(const FInputActionValue& Value);
	void Fire(const FInputActionValue& Value);
	void Reload();
	void SpawnActor();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
