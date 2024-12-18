#include "PongBorders.h"
#include "PongGameStateBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APongBorders::APongBorders()
{
	PrimaryActorTick.bCanEverTick = true;

	// SCENE COMPONENT
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);
	
	// STATIC MESH COMPONENT
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	// BOX COMPONENT
	BorderCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BorderBox"));
	RootComponent = BorderCollision;
	BorderCollision->SetBoxExtent(FVector(500.f, 500.f, 100.f));
	BorderCollision->OnComponentHit.AddDynamic(this, &APongBorders::OnBorderHit);
	BorderCollision->SetCollisionProfileName(TEXT("BlockAll"));
	BorderCollision->SetNotifyRigidBodyCollision(true);
}

/*
 * Default begin play method
 */
void APongBorders::BeginPlay()
{
	Super::BeginPlay();
}

/*
 * Default tick function
 */
void APongBorders::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
 * Called whenever a border component gets hit.
 * There are currently 4 borders placed, all forming together a square board.
 * Only 1 side of each of the borders can be "hit", so I can apply this exact
 * same logic for each of the borders, without needing to specify a "top" or
 * "bottom" border.
 */
void APongBorders::OnBorderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APongGameStateBase* PongGameState = GetWorld()->GetGameState<APongGameStateBase>();
	
	if (!PongGameState)
	{
		return;
	}
	
	FVector ImpactNormal = Hit.ImpactNormal;

	// Right side of the UBox was Hit
	if (ImpactNormal.X > 0.8f)
	{
		if (SoundCue)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SoundCue, GetActorLocation());
		}
		
		//UE_LOG(LogTemp, Log, TEXT("Right Hit"));
		PongGameState->UpdateScore(true);
		PongGameState->ResetGame();
	}
	
	// Left side of the UBox was Hit
	else if (ImpactNormal.X < -0.8f)
	{
		if (SoundCue)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SoundCue, GetActorLocation());
		}
		
		//UE_LOG(LogTemp, Log, TEXT("Left Hit"));
		PongGameState->UpdateScore(false);
		PongGameState->ResetGame();
	}
}
