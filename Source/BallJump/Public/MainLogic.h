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
	AMainLogic();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = Spawn)
		TSubclassOf<ABlock> BlockSpawn;
	UPROPERTY(EditAnywhere, Category = Spawn)
		TSubclassOf<ACloud> CloudSpawn;

private:
    float TimerRate = 0.2f;
    float Speed{0};
	AActor* downBlockPointer{ nullptr };
	AActor* upBlockPointer{ nullptr };
	AActor* cloudPointer{ nullptr };
	UMyGameInstance* GameInst{ nullptr };
	FIntPoint ViewSize;
	FTimerHandle TimerHandle;
	
	void ChangeScreenSize();
    void GenerateOnStartCloud();
    void GenerateOnStartBlock();
    void GenerateNewCloud();
    void GenerateNewBlock(AActor*& Block, bool up);
    float NewScaleX();
    void SpeedOnStart();
	void SpeedCalc();
	void ScoreCalc();
	float SpeedClamp(float Speedtmp);
	void OnTimerFired();
};