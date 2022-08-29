// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyGameInstance.h"
#include "Components/SphereComponent.h"
#include "BallPawn.generated.h"

UCLASS()
class BALLJUMP_API ABallPawn : public APawn
{
	GENERATED_BODY()



public:
	// Sets default values for this pawn's properties
	ABallPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* BallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Speed = 5.0f;

private:
	FVector BallLocation;
	FRotator CurrentRotation;
	FVector Gravity{ FVector(0.0f, 0.0f, 0.0f) };
	UMyGameInstance* GameInst{ nullptr };
	USphereComponent* prim{ nullptr };
	bool CanJump{ false };
	bool IsDown{ true };

	
	//void Movement();
	//void Pitch();
	void ChangeFloor();
	void CheckDead();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp
	,FVector NormalImpulse, const FHitResult& Hit);

};
