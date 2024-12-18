#include "PongHUD.h"

/*
 * Draw the HUD onto the top left corner of the display/camera display
 */
void APongHUD::DrawHUD()
{
	Super::DrawHUD();

	FString ScoreText = FString::Printf(TEXT("Computer: %d   Player: %d"), ComputerScore, PlayerScore);
	DrawText(ScoreText, FColor::White, 25, 25, nullptr, 3.0f);

	FString StatsText = FString::Printf(TEXT("Ball Speed: %d   Computer Difficulty: %d"), BallSpeed, ComputerDifficulty);
	DrawText(StatsText, FColor::White, 25, 75, nullptr, 3.0f);
}

/*
 * Updates the score variables
 */
void APongHUD::UpdateScore(int ComputerScoreNew, int PlayerScoreNew)
{
	ComputerScore = ComputerScoreNew;
	PlayerScore = PlayerScoreNew;
}

/*
 * Updates the speed variable
 */
void APongHUD::UpdateSpeed(int BallSpeedNew)
{
	BallSpeed = BallSpeedNew;
}

/*
 * Updates the difficulty variable
 */
void APongHUD::UpdateDifficulty(int ComputerDifficultyNew)
{
	ComputerDifficulty = ComputerDifficultyNew;
}
