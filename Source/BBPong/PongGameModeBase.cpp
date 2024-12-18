#include "PongGameModeBase.h"

#include "PongGameStateBase.h"
#include "PongHUD.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

/*
 * Set the default HUD class
 */
APongGameModeBase::APongGameModeBase()
{
	HUDClass = APongHUD::StaticClass();
}

/*
 * Set the Game state class
 * Set the camera to be facing towards the game board
 */
void APongGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Game State
	GameStateClass = APongGameStateBase::StaticClass();
	
	// Camera Location / Rotation (Pointing towards the center of the board)
	FVector CameraLocation = FVector(0.0f, 500.0f, 120.0f);
	FVector TargetLocation = FVector(0.0f, 0.0f, 120.0f);
	FRotator CameraRotation = (TargetLocation - CameraLocation).Rotation();

	// Spawn the Camera, set as the Main Camera
	ACameraActor* CameraActor = GetWorld()->SpawnActor<ACameraActor>(ACameraActor::StaticClass(), CameraLocation, CameraRotation);
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(CameraActor);
}
