#pragma once

#include "CoreMinimal.h"
#include "PongBall.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PongComputerPaddle.generated.h"

UCLASS()
class BBPONG_API APongComputerPaddle : public AActor
{
	GENERATED_BODY()
	
public:	
	APongComputerPaddle(); // Sets default values

	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category = "ComputerActor")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "ComputerActor")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ComputerActor")
	UBoxComponent* PaddleCollision;

	UPROPERTY(EditAnywhere, Category = "ComputerActor")
	float Difficulty = 8.0f; // Determines how fast the paddle will move

	UPROPERTY(EditAnywhere, Category = "ComputerActor")
	APongBall* Ball;

	UPROPERTY(EditAnywhere, Category = "ComputerActor")
	FVector InitialLocation;

	UPROPERTY(EditAnywhere, Category = "ComputerActor")
	FVector NewLocation;

	UPROPERTY(EditAnywhere, Category = "ComputerActor")
	float TimeTracker = 0.0f;

protected:
	virtual void BeginPlay() override; // Called when game starts/is spawned
};
