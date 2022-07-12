// Fill out your copyright notice in the Description page of Project Settings.

#include "Block.h"

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
        FVector CurrentLocation = GetActorLocation();
        if (GetWorld())
        {
            if(GameInst)
                CurrentLocation.X = CurrentLocation.X - 20 * DeltaTime * GameInst->GetMySpeed();
            else
                CurrentLocation.X = CurrentLocation.X - 20 * DeltaTime * 5;
            SetActorLocation(CurrentLocation);


        }
}

void ABlock::CheckToDestroy()
{
    ActorScale = this->GetActorScale3D();
    FVector CurrentLocation = GetActorLocation();
    UGameViewportClient* Viewport = GetWorld()->GetGameViewport();
    FIntPoint ViewSize = Viewport->Viewport->GetSizeXY();
    
    if (CurrentLocation.X<-((ViewSize.X/2 + ((ActorScale.X * 50)/2))+350))
    {
        Destroy();
    }
}


