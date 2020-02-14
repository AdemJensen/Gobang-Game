// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessBoardIndicator.generated.h"

UCLASS()
class GOBANG_API AChessBoardIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessBoardIndicator();

	UPROPERTY(Category = "Properties", VisibleDefaultsOnly, BlueprintReadOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Properties", VisibleDefaultsOnly, BlueprintReadOnly)
		class UMaterial* PlayerMaterial;

	UPROPERTY(Category = "Properties", VisibleDefaultsOnly, BlueprintReadOnly)
		class UMaterial* LastMaterial;

	bool IsPlayerNow;

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void SetIndicatorColor(bool IsPlayer);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void SetIndicatorVisibility(bool Visibility);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
