// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Math/Vector2D.h"
#include "ChessBoardManager.h"
#include "ChessLocationTrigger.generated.h"

UCLASS()
class GOBANG_API AChessLocationTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessLocationTrigger();

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void InitUtility(FVector2D size, int32 Coord_X, int32 Coord_Y, AChessBoardManager* WorldOwnerBoard);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void SetTaken(bool Taken) { IsTaken = Taken; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* Existance;

	UFUNCTION()
		void TriggerClicked(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	int32 Coordinate_X;
	int32 Coordinate_Y;
	bool IsTaken = false;

	AChessBoardManager* OwnerBoard;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
