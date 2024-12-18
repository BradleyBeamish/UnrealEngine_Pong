#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PongGameModeBase.generated.h"

UCLASS()
class BBPONG_API APongGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	APongGameModeBase();
	
	virtual void BeginPlay() override;
};
