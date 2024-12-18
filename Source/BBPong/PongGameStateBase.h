#pragma once

#include "CoreMinimal.h"
#include "PongBall.h"
#include "PongComputerPaddle.h"
#include "PongHUD.h"
#include "PongPlayerPaddle.h"
#include "GameFramework/GameStateBase.h"
#include "PongGameStateBase.generated.h"

UCLASS()
class BBPONG_API APongGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	int ComputerScore = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameState")
	int PlayerScore = 0;

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void UpdateScore(bool bLeftSideHit);

	UPROPERTY(BlueprintReadWrite, Category = "GameState")
	APongHUD* PongHUD;

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void UpdateSpeed(float Speed);

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void UpdateDifficulty(float Difficulty);

	UFUNCTION(BlueprintCallable, Category = "GameState")
	void ResetGame();

	UPROPERTY(BlueprintReadWrite, Category = "GameMode")
	APongBall* Ball;

	UPROPERTY(BlueprintReadWrite, Category = "GameMode")
	APongPlayerPaddle* PlayerPaddle;

	UPROPERTY(BlueprintReadWrite, Category = "GameMode")
	APongComputerPaddle* ComputerPaddle;
};
