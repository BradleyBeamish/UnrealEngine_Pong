#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PongHUD.generated.h"

UCLASS()
class BBPONG_API APongHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void DrawHUD() override;

	void UpdateScore(int ComputerScoreNew, int PlayerScoreNew);

	void UpdateSpeed(int BallSpeedNew);

	void UpdateDifficulty(int ComputerDifficultyNew);

private:
	int ComputerScore = 0;
	int PlayerScore = 0;
	int BallSpeed = 300;
	int ComputerDifficulty = 8;
};
