// Fill out your copyright notice in the Description page of Project Settings.

#include "Block.h"
#include <cassert>

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BlockMesh = CreateDefaultSubobject <UStaticMeshComponent>("BlockMesh");
	SetRootComponent(BlockMesh);
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
    GameInst = Cast<UMyGameInstance>(GetGameInstance());
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    
    HandleMovement(DeltaTime);
    CheckToDestroy();
    
}

void ABlock::HandleMovement(double DeltaTime)
{
    check(GameInst);

    //block movement every frame
    FVector CurrentLocation = GetActorLocation();
    CurrentLocation.X -= 20 * DeltaTime * (static_cast<float>(GameInst->GetMySpeed()));
    SetActorLocation(CurrentLocation);
}

void ABlock::CheckToDestroy()
{
    // Get screen size
    check(GameInst);
    FVector CurrentLocation = GetActorLocation();
    FVector CurrentScale = GetActorScale();
    FIntPoint ViewSize = GameInst->GetMyViewSize();
    //if block out of the screen - destroy
    //
    if ((CurrentLocation.X + (CurrentScale.X * 50.0f)) < -(ViewSize.X*3))
    {
        Destroy();
    }
}


