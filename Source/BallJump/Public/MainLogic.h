// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Block.h"
#include "Cloud.h"
#include "MyGameInstance.h"
#include "MainLogic.generated.h"

UCLASS()

class BALLJUMP_API AMainLogic : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainLogic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Spawn)
		TSubclassOf<ABlock> BlockSpawn;

	UPROPERTY(EditAnywhere, Category = Spawn)
		TSubclassOf<ACloud> CloudSpawn;

	//UPROPERTY(EditAnywhere, Category = Spawn)
	//	TSubclassOf<UMyGameInstance> GameInstance;

	//UPROPERTY(EditAnywhere, Category = Spawn)
		

private:
	AActor* DownBlock{nullptr};
	AActor* UpBlock{ nullptr };
	AActor* CloudBP{ nullptr };
	UMyGameInstance* GameInst{ nullptr };
	
	FIntPoint ViewSize;
	int32 Speed{0};
	int32 Score{ 0 };
	FTimerHandle TimerHandle;
	float TimerRate = 5.0f;
	
	void ScreenSize();
	void CheckAndSpawnBlock();
	void CheckAndSpawnCloud();
	void SpawnActors(TSubclassOf<ACloud> ActorSpawn, FVector& Location, FRotator& Rotation);
	void SpeedCalc();
	int32 SpeedClamp(int32 Speedtmp);
	void OnTimerFired();
};
