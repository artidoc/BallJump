// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "MyGameInstance.h"
#include "Cloud.generated.h"

UCLASS()
class BALLJUMP_API ACloud : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACloud();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Sprite)
		UPaperSprite* CloudSprite;

	UPROPERTY(EditAnywhere)
		UPaperSpriteComponent* Sprite;

private:
	
	FVector InitialLocation;
	double CloudSpeed;
	UMyGameInstance* GameInst{ nullptr };

	void HandleMovement(double DeltaTime);
	void CheckToDestroy();

	
};
