// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GobangPlayerController.h"
#include "GobangPlayerPawn.h"
#include "Managers/GameManagerBase.h"
#include "GobangGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GOBANG_API AGobangGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGobangGameModeBase();

	AGameManagerBase* GameManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
