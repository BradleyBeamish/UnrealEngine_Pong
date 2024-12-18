#include "PongBall.h"
#include "PongGameStateBase.h"
#include "PongPlayerPaddle.h"

// Sets default values
APongBall::APongBall()
{
	PrimaryActorTick.bCanEverTick = true; // Call Tick() every frame

	// SPHERE COMPONENT
	BallCollision = CreateDefaultSubobject<USphereComponent>(TEXT("BallCollision"));
	RootComponent = BallCollision;
	BallCollision->SetCollisionProfileName(TEXT("BlockAll"));

	// Lock Translations / Rotations (2D game)
	BallCollision->GetBodyInstance()->bLockXRotation = true;
	BallCollision->GetBodyInstance()->bLockYRotation = true;
	BallCollision->GetBodyInstance()->bLockZRotation = true;
	BallCollision->GetBodyInstance()->bLockXTranslation = true;
	BallCollision->GetBodyInstance()->bLockYTranslation = true;
	BallCollision->GetBodyInstance()->bLockZTranslation = true;

	// STATIC MESH COMPONENT
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetupAttachment(RootComponent);

	// MOVEMENT COMPONENT
	BallMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BallMovement"));
	BallMovement->bShouldBounce = true;
	BallMovement->ProjectileGravityScale = 0.0f;
	BallMovement->Bounciness = 1.0f;
	BallMovement->Friction = 0.0f;
	BallMovement->InitialSpeed = InitialSpeed;

	// ON-HIT COMPONENT
	BallCollision->OnComponentHit.AddDynamic(this, &APongBall::OnBallHit);
}

/*
 * Ensure the ball starts moving from the center of the game right away
 */
void APongBall::BeginPlay()
{
	Super::BeginPlay();
	BallMovement->Velocity = FVector(1.f, 0.f, 0.f) * InitialSpeed; // Move only in X axis
}

/*
 * Default tick function
 */
void APongBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*
 * OnComponentHit()
 * Gets called whenever the ball hits an object.
 * If the object it hits is the paddle, the position on the paddle will be taken into account
 * for a new velocity / direction.
 */
void APongBall::OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != this) // Ensure that the hit did get hit by something, and that something was not itself
	{
		if (APongPlayerPaddle* Paddle = Cast<APongPlayerPaddle>(OtherActor))
		{
			// Get the position of the ball on the paddle
			float PaddlePosition = (GetActorLocation().Z - Paddle->GetActorLocation().Z) / Paddle->PaddleCollision->GetScaledBoxExtent().Z;
			
			PaddlePosition = FMath::Clamp(PaddlePosition, -1.0f, 1.0f); // Normalize hit position between -1 and 1

			// Update the HUD with the new speed (Increases by 50 every time the player's paddle hits it)
			float NewSpeed = BallMovement->Velocity.Size() + 50.0f;
			APongGameStateBase* PongGameState = GetWorld()->GetGameState<APongGameStateBase>();
			PongGameState->UpdateSpeed(NewSpeed);
			
			FVector NewDirection = FVector(1.0f, 0.0f, PaddlePosition).GetSafeNormal(); // Adjust angle of ball reflection

			BallMovement->Velocity = NewDirection * NewSpeed; // Update Velocity of Ball
		}
	}
}
