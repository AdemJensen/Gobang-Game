// This is a private project, cannot be put at commercial use.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Basics/UnexpectedGameActionType.h"
#include "GamePlayerType.h"
#include "../Basics/ChessType.h"
#include "GamePlayerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEventDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRetractEventDelegate, FIntPoint, RetractPosition1, FIntPoint, RetractPosition2);
UCLASS()
class GOBANG_API AGamePlayerBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGamePlayerBase();

	UFUNCTION(BlueprintCallable, Category = "Game Actions")
		virtual void OnGameStart() { OnGameStartDelegate.Broadcast(); }	// Called outside, needs to implement inside.
	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Game Actions")
		FEventDelegate OnGameStartDelegate;

	UFUNCTION(BlueprintCallable, Category = "Game Actions")
		virtual void OnRoundStart() { OnRoundStartDelegate.Broadcast(); }	// Called outside, needs to implement inside.
	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Game Actions")
		FEventDelegate OnRoundStartDelegate;

	UFUNCTION(BlueprintCallable, Category = "Game Actions")
		virtual void OnInterrupt() { OnInterruptDelegate.Broadcast(); }	// Called outside, needs to implement inside.
	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Game Actions")
		FEventDelegate OnInterruptDelegate;

	/**
	This function is called when either of the player called "DoRetract."
	*/
	UFUNCTION(BlueprintCallable, Category = "Game Actions")
		virtual void OnRetract(FIntPoint RetractPosition1, FIntPoint RetractPosition2) { OnRetractDelegate.Broadcast(RetractPosition1, RetractPosition2); }	// Called outside, needs to implement inside.
	UPROPERTY(BlueprintAssignable, EditAnywhere, Category = "Game Actions")
		FRetractEventDelegate OnRetractDelegate;

	UFUNCTION(BlueprintCallable, Category = "Game Info")
		void SetChessType(EChessType Type) { ChessType = Type; }
	UFUNCTION(BlueprintCallable, Category = "Game Info")
		EChessType GetChessType() { return ChessType; }

	UFUNCTION(BlueprintCallable, Category = "Game Info")
		void SetRetractRemainTimes(int32 RemainTimes) { RetractRemainTimes = RemainTimes; }
	UFUNCTION(BlueprintCallable, Category = "Game Info")
		int32 GetRetractRemainTimes() { return RetractRemainTimes; }

	UFUNCTION(BlueprintCallable, Category = "Game Info")
		virtual EGamePlayerType GetPlayerType() { return EGamePlayerType::UNKNOWN; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		AGameModeBase* GetGameMode();

	UPROPERTY(EditAnywhere, Category = "Game Info")
		EChessType ChessType = EChessType::UNKNOWN;

	UPROPERTY(EditAnywhere, Category = "Game Info")
		int32 RetractRemainTimes = 0;

	UFUNCTION(BlueprintCallable, Category = "Game Actions")
		virtual void DoRoundOver(FIntPoint ActionLocation);

	UFUNCTION(BlueprintCallable, Category = "Game Actions")
		virtual void DoSurrounder();

	UFUNCTION(BlueprintCallable, Category = "Game Actions")
		virtual void DoUnexpectedAction(EUnexpectedGameActionType Type);

	UFUNCTION(BlueprintCallable, Category = "Game Actions")
		virtual void DoRetract();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
