// Fill out your copyright notice in the Description page of Project Settings.


#include "InvadersPlayerController.h"
#include "InvadersCamera.h"
#include "Kismet/GameplayStatics.h"

void AInvadersPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	AActor* CameraActor = UGameplayStatics::GetActorOfClass(GetWorld(), AInvadersCamera::StaticClass());
	CameraActor = Cast<class AInvadersCamera>(CameraActor);
	if (CameraActor)
	{
		SetViewTargetWithBlend(CameraActor);
	}
}
