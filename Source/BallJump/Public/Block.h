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
	ABlock();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BlockMesh;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UMyGameInstance* GameInst{ nullptr };
};