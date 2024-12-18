#include "PongGameStateBase.h"
#include "Kismet/GameplayStatics.h"

/*
 * Update the score variables, then update score in HUD class
 */
void APongGameStateBase::UpdateScore(bool LeftSideHit)
{
	if (LeftSideHit)
	{
		PlayerScore++;
	}
	else
	{
		ComputerScore++;
	}
	
	PongHUD = Cast<APongHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	if (PongHUD)
	{
		PongHUD->UpdateScore(ComputerScore, PlayerScore); // Update the HUD
	}
}

/*
 * Update the speed variable, then update in HUD class
 */
void APongGameStateBase::UpdateSpeed(float Speed)
{
	PongHUD = Cast<APongHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	if (PongHUD)
	{
		PongHUD->UpdateSpeed(Speed); // Update the HUD
	}
}

/*
 * Update difficulty variable, then update within the HUD class
 */
void APongGameStateBase::UpdateDifficulty(float Difficulty)
{
	PongHUD = Cast<APongHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	if (PongHUD)
	{
		PongHUD->UpdateDifficulty(Difficulty); // Update the HUD
	}
}

/*
 * Reset the game back to the initial state (maintains score)
 */
void APongGameStateBase::ResetGame()
{
	// Get references to the ball, paddles, and HUD
	Ball = Cast<APongBall>(UGameplayStatics::GetActorOfClass(GetWorld(), APongBall::StaticClass()));
	PlayerPaddle = Cast<APongPlayerPaddle>(UGameplayStatics::GetActorOfClass(GetWorld(), APongPlayerPaddle::StaticClass()));
	ComputerPaddle = Cast<APongComputerPaddle>(UGameplayStatics::GetActorOfClass(GetWorld(), APongComputerPaddle::StaticClass()));
	
	// Reset Ball
	if (Ball)
	{
		// Set ball position to the center of the game area
		Ball->SetActorLocation(FVector(0.0f, 0.0f, 150.0f));
		Ball->BallMovement->Velocity = FVector(1.f, 0.f, 0.f) * Ball->BallMovement->InitialSpeed;
	}

	// Reset Player Paddle
	if (PlayerPaddle)
	{
		PlayerPaddle->SetActorLocation(FVector(-270.0f, 0.0f, 150.0f));
	}

	// Reset Computer Paddle
	if (ComputerPaddle)
	{
		ComputerPaddle->SetActorLocation(FVector(270.0f, 0.0f, 150.0f));
		ComputerPaddle->Difficulty = 5.0f;
	}
}
