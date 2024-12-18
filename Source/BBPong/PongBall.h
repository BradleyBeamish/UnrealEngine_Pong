#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PongBall.generated.h"

UCLASS()
class BBPONG_API APongBall : public AActor
{
	GENERATED_BODY()
	
public:	
	APongBall(); // Sets default values

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* BallCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
	UStaticMeshComponent* BallMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	UProjectileMovementComponent* BallMovement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float InitialSpeed = 250.f;
	
	UFUNCTION()
	void OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override; // Called when the game starts
};
