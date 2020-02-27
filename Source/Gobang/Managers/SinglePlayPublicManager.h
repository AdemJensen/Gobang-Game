// This is a private project, cannot be put at commercial use.

#pragma once

#include "CoreMinimal.h"
#include "PublicManagerBase.h"
#include "../Basics/GameStage.h"
#include "../Basics/ChessType.h"
#include "../Basics/BanMode.h"
#include "SinglePlayPublicManager.generated.h"

/**
 * 
 */
UCLASS()
class GOBANG_API ASinglePlayPublicManager : public APublicManagerBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Game Info")
		void SetAiDifficulty(int32 DifficultyLevel) { AiDifficulty = DifficultyLevel; }
	UFUNCTION(BlueprintCallable, Category = "Game Info")
		int32 GetAiDifficulty() { return AiDifficulty; }

	UFUNCTION(BlueprintCallable, Category = "Game Info")
		ASinglePlayPublicManager* InitSinglePlayPublicManager(int32 DifficultyLevel, int32 BanModeLevel, int32 HintCoolDownLevel, int32 RetractTimesLevel, int32 RoundTimeLimitLevel);
	UFUNCTION(BlueprintCallable, Category = "Game Info")
		ASinglePlayPublicManager* InitSinglePlayPublicManagerByValue(int32 DifficultyValue, EBanMode BanModeValue, float HintCoolDownValue, int32 RetractTimesValue, float RoundTimeLimitValue);

protected:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Info")
		int32 AiDifficulty = 0;	// 1~3.
	
};
