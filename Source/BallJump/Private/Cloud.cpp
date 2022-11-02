#include "Cloud.h"
#include "MainLogic.h"

ACloud::ACloud()
{
 	PrimaryActorTick.bCanEverTick = true;
	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("CloudSprite"));
	SetRootComponent(Sprite);
	Sprite->SetSprite(CloudSprite);

}

void ACloud::BeginPlay()
{
	Super::BeginPlay();
    GameInst = Cast<UMyGameInstance>(GetGameInstance());
}

void ACloud::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    check(GameInst);
	GameInst->HandleMovement(this,DeltaTime,true);
    GameInst->CheckIfOutOfTheScreenAndDestroy(this);
}