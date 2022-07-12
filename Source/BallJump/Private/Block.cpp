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
                CurrentLocation.X = CurrentLocation.X - 20 * DeltaTime * GameInst->GetSpeed();
            else
                CurrentLocation.X = CurrentLocation.X - 20 * DeltaTime * 5;
            //if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.f, FColor::Red, FString::Printf(TEXT("Speed=%i"), ));
            SetActorLocation(CurrentLocation);

            //UE_LOG(LogTemp, Warning, TEXT("CurrentLocation.X=%.2f"), CurrentLocation.X);

        }
}

void ABlock::CheckToDestroy()
{
    ActorScale = this->GetActorScale3D();
    FVector CurrentLocation = GetActorLocation();
    UGameViewportClient* Viewport = GetWorld()->GetGameViewport();
    FIntPoint ViewSize = Viewport->Viewport->GetSizeXY();
    //if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("X = %i , Y = %i, BlockView=%f, Sum=%f"),ViewSize.X, ViewSize.Y, ((ActorScale.X*50)/2), ((ViewSize.X + ((ActorScale.X * 50) / 2)))));

    if (CurrentLocation.X<-((ViewSize.X/2 + ((ActorScale.X * 50)/2))+350))
    {
        Destroy();
    }
}


