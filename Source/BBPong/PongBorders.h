#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"
#include "PongBorders.generated.h"

UCLASS()
class BBPONG_API APongBorders : public AActor
{
	GENERATED_BODY()
	
public:
	APongBorders(); // Sets default values

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Borders")
	UBoxComponent* BorderCollision;

	UPROPERTY(EditAnywhere, Category="Borders")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, Category = "Borders")
	USceneComponent* MeshSceneComponent;

	UPROPERTY(EditAnywhere, Category = "Borders")
	UStaticMeshComponent* StaticMeshComponent;
	
	UPROPERTY(EditAnywhere, Category = "Borders")
	USoundCue* SoundCue;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBorderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void BeginPlay() override; // Called when the game starts
};
