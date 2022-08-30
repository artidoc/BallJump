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
    GameInst = Cast<UMyGameInstance>(GetGameInstance());
}

// Called every frame
void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    check(GameInst);
    //cloud movement from right to left
	GameInst->HandleMovement(this,DeltaTime,true);
    // destroy object if it is out of the screen
    GameInst->CheckToDestroy(this);
}