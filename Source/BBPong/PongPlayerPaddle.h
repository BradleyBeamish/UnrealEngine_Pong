#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "PongPlayerPaddle.generated.h"

UCLASS()
class BBPONG_API APongPlayerPaddle : public APawn
{
	GENERATED_BODY()

public:
	APongPlayerPaddle(); // Sets default values for this pawn's properties
	
	virtual void Tick(float DeltaTime) override; // Called every frame
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Bind functionality to input

	UPROPERTY(EditAnywhere, Category = "Pawn")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Pawn")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UBoxComponent* PaddleCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pawn")
	float PaddleSpeed = 500.0f;

protected:
	virtual void BeginPlay() override; // Called when the game starts or when spawned

private:
	float MoveUpAmount;
	
	void MoveVertically(float Amount);
};
