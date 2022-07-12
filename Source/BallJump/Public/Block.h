// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameInstance.h"
#include "Block.generated.h"

UCLASS()
class BALLJUMP_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BlockMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = Spawn)
		AActor* MainLogicBP{nullptr};

private:
	FVector InitialLocation;
	FVector ActorScale;
	UMyGameInstance* GameInst{ nullptr };


	void HandleMovement(double DeltaTime);
	void CheckToDestroy();

};