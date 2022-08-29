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

    //cloud movement from right to left
	HandleMovement(DeltaTime);
    
    
    //check if cloud is going out from the screen and then delete it
    CheckToDestroy();
}

void ACloud::HandleMovement(double DeltaTime)
{
    check(GameInst);
    FVector CurrentLocation = GetActorLocation();
    CurrentLocation.X -= 20 * DeltaTime * (static_cast<float>(GameInst->GetMySpeed())/2.0f);
    SetActorLocation(CurrentLocation);


}

void ACloud::CheckToDestroy()
{
    // Get screen size
    check(GameInst);
    FVector CurrentLocation = GetActorLocation();
    FIntPoint ViewSize = GameInst->GetMyViewSize();

    // if block out of the screen - destroy
    if (CurrentLocation.X < -(ViewSize.X*3))
    {
        Destroy();
    }
}
