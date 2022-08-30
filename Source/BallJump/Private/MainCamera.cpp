// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCamera.h"

// Sets default values
AMainCamera::AMainCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	Camera = CreateDefaultSubobject<UCameraComponent>("MainCamera");
	SetRootComponent(Camera);

	//Camera->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);
	
}

// Called every frame
void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

