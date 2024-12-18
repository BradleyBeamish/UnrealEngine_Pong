#include "PongComputerPaddle.h"
#include "PongGameStateBase.h"

/*
 * Set up the Paddle
 */
APongComputerPaddle::APongComputerPaddle()
{
	PrimaryActorTick.bCanEverTick = true; // Calls Tick() every frame

	// SCENE COMPONENT
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	// STATIC MESH COMPONENT
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	// BOX COLLISION COMPONENT
	PaddleCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("PaddleCollision"));
	PaddleCollision->SetupAttachment(SceneComponent);

	// Disable Collisions on Static Mesh, Enable Collisions on the box component
	PaddleCollision->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

/*
 * Sets the position of the computer paddle
 */
void APongComputerPaddle::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(270.0f, 0.0f, 150.0f)); // Ensure paddle is in the correct position on the board
	InitialLocation = GetActorLocation();
}

/*
 * Move the paddle towards the ball
 * The paddle will become faster/more difficult every 5 seconds
 */
void APongComputerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimeTracker += DeltaTime;

	// Every 5 seconds, increase the difficulty, and update the HUD
	if (TimeTracker >= 5.0f)
	{
		Difficulty += 1.0f;
		APongGameStateBase* PongGameState = GetWorld()->GetGameState<APongGameStateBase>();
		PongGameState->UpdateDifficulty(Difficulty);

		TimeTracker = 0.0f;
	}

	// Implemented using the pseudocode from Brightspace

	if (Ball != nullptr)
	{
		// Move towards ball
		FVector BallLocation = Ball->GetActorLocation();
		FVector TargetLocation = GetActorLocation();

		TargetLocation.Z = BallLocation.Z; // Match Z coords with the ball

		// Move the paddle towards the ball
		NewLocation = FMath::VInterpTo(GetActorLocation(), TargetLocation, DeltaTime, Difficulty);
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("No Ball Found"));
		NewLocation = FMath::VInterpTo(GetActorLocation(), InitialLocation, DeltaTime, Difficulty);
	}

	SetActorLocation(NewLocation);
}
