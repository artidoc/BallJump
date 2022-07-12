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
	int32 GetScore(){ return Score; }
	int32 GetSpeed(){ return FMath::Clamp(Speed, 0, 45); }
	bool GetIsDead() { return IsDead; }
	void SetScore(int32 ScoreTmp) {Score = ScoreTmp;}
	void SetSpeed(int32 SpeedTmp) { Speed = SpeedTmp; }
	void SetIsDead(bool Dead) { IsDead = Dead; }
	


private:
	int32 Score{0};
	int32 Speed{0};
	bool IsDead{false};
	
};
