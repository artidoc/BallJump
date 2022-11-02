#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "MainCamera.generated.h"

UCLASS()
class BALLJUMP_API AMainCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	AMainCamera();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

};
