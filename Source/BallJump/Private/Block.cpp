#include "Block.h"
#include <cassert>

ABlock::ABlock()
{
 	PrimaryActorTick.bCanEverTick = true;
	BlockMesh = CreateDefaultSubobject <UStaticMeshComponent>("BlockMesh");
	SetRootComponent(BlockMesh);
}

void ABlock::BeginPlay()
{
	Super::BeginPlay();
    GameInst = Cast<UMyGameInstance>(GetGameInstance());
}

void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    check(GameInst);
    GameInst->HandleMovement(this, DeltaTime, false);
    GameInst->CheckIfOutOfTheScreenAndDestroy(this);
    
}