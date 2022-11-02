#include "MainCamera.h"

AMainCamera::AMainCamera()
{
 	PrimaryActorTick.bCanEverTick = false;
	Camera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	SetRootComponent(Camera);

}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	
}

void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

