// Fill out your copyright notice in the Description page of Project Settings.


#include "Cloud.h"
#include "MainLogic.h"

// Sets default values
ACloud::ACloud()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CloudSprite"));
	SetRootComponent(Sprite);
	Sprite->SetSprite(CloudSprite);

}

// Called when the game starts or when spawned
void ACloud::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
    GameInst = Cast<UMyGameInstance>(GetGameInstance());
	
}

// Called every frame
void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMovement(DeltaTime);
    CheckToDestroy();
}

void ACloud::HandleMovement(double DeltaTime)
{
    FVector CurrentLocation = GetActorLocation();
    if (GetWorld())
    {
        CurrentLocation.X = CurrentLocation.X - 20 * DeltaTime * (static_cast<float>(GameInst->GetSpeed())/2.0f);
        //if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 9999.f, FColor::Red, FString::Printf(TEXT("CurrentLocation.X=%f"), CurrentLocation.X/1531));
        SetActorLocation(CurrentLocation);

        //UE_LOG(LogTemp, Warning, TEXT("CurrentLocation.X=%.2f"), CurrentLocation.X);

    }
}

void ACloud::CheckToDestroy()
{
    FVector CurrentLocation = GetActorLocation();
    UGameViewportClient* Viewport = GetWorld()->GetGameViewport();
    FIntPoint ViewSize = Viewport->Viewport->GetSizeXY();
    //if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, FString::Printf(TEXT("X = %i , Y = %i, BlockView=%f, Sum=%f"),ViewSize.X, ViewSize.Y, ((ActorScale.X*50)/2), ((ViewSize.X + ((ActorScale.X * 50) / 2)))));

    if (CurrentLocation.X < -(ViewSize.X / 2 + 150 + 100))
    {
        Destroy();
    }
}
