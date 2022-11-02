// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BALLJUMP_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	int32 GetMyScore(){ return Score; }
	int32 GetMyHighScore() { return HighScore; }
	float GetMySpeed(){ return FMath::Clamp(Speed, 0.0f, 50.0f); }
	bool GetMyIsDead() { return IsDead; }
	FIntPoint GetMyViewSize() { return ViewSize; }
	void SetScore(int32 ScoreTmp) {Score = ScoreTmp;}
	void SetHighScore(int32 ScoreTmp) { HighScore = ScoreTmp; }
	void SetSpeed(float SpeedTmp) { Speed = SpeedTmp; }
	void SetIsDead(bool Dead) { IsDead = Dead; }
	void SetViewSize(FIntPoint ViewSizeTmp) { ViewSize = ViewSizeTmp; }

	UPROPERTY(BlueprintReadOnly)
	int32 Score {0};
	UPROPERTY(BlueprintReadWrite)
	int32 HighScore {0};
	UPROPERTY(BlueprintReadOnly)
	float Speed {0};
	UPROPERTY(BlueprintReadOnly)
	bool IsDead{ false };
	UPROPERTY(BlueprintReadOnly)
	FIntPoint ViewSize{1920,1080};

	void CheckIfOutOfTheScreenAndDestroy(AActor* Objected);
    void HandleMovement(AActor* Objected, double DeltaTime, bool cloud);
};
