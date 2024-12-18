#include "PongPlayerPaddle.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"

/*
 * Sets up the components
 */
APongPlayerPaddle::APongPlayerPaddle()
{
	PrimaryActorTick.bCanEverTick = true;

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
 * The Pawn Paddle will spawn in on start, ensure it spawns into the correct position
 */
void APongPlayerPaddle::BeginPlay()
{
	Super::BeginPlay();
	SetActorLocation(FVector(-270.0f, 0.0f, 150.0f));
}

/*
 * Sets the next position for the paddle
 */
void APongPlayerPaddle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MoveUpAmount != 0.0f && Controller != nullptr)
	{
		FVector NewLocation = GetActorLocation();
		NewLocation.Z += MoveUpAmount * PaddleSpeed * DeltaTime;  // Move along the Z-axis
		SetActorLocation(NewLocation);
	}
}

/*
 * Called to bind functionality to input
 */
void APongPlayerPaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveUp", this, &APongPlayerPaddle::MoveVertically); // Bind the vertical movement axis
}

/*
 * Handle vertical movement input
 */
void APongPlayerPaddle::MoveVertically(float Amount)
{
	MoveUpAmount = Amount; // Can be negative or positive depending on whether it's moving up or down
}
