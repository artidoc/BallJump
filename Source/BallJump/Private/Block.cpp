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
    
    check(GameInst);
    GameInst->HandleMovement(this, DeltaTime, false);
    //destroy object if it is out of the screen
    GameInst->CheckToDestroy(this);
    
}