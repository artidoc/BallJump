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
	ABallPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
		USphereComponent* BallMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float Speed = 5.0f;

private:
    bool CanJump{false};
    bool IsDown{true};
	FVector BallLocation;
	FRotator CurrentRotation;
	FVector Gravity{ FVector(0.0f, 0.0f, 0.0f) };
	UMyGameInstance* GameInst{ nullptr };
	USphereComponent* prim{ nullptr };
	

	void ChangeFloor(float num,bool Down);
    void ActiveButton();
	void CheckDead();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp
	,FVector NormalImpulse, const FHitResult& Hit);

};
