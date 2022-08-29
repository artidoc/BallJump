// Fill out your copyright notice in the Description page of Project Settings.

#include "BallPawn.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"


// Sets default values
ABallPawn::ABallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	BallMesh = CreateDefaultSubobject<USphereComponent>("BallMesh");
	SetRootComponent(BallMesh);
	
	//some parameters for ball pawn
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetNotifyRigidBodyCollision(true);
	BallMesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	
}

// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	GameInst = Cast<UMyGameInstance>(GetGameInstance());
	BallMesh->OnComponentHit.AddDynamic(this, &ABallPawn::OnHit);


}

// Called every frame
void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	prim = Cast<USphereComponent>(this->GetRootComponent());
	
	//change gravity direction
	check(prim)
	prim->AddForce(Gravity,NAME_None, true);
	
	//check if ball out of the blocks
	CheckDead();
}

void ABallPawn::ChangeFloor()
{
	if (CanJump)
	{
		if (IsDown)
		{
			Gravity = FVector(0.0f, 0.0f, 2500.0f); 
			IsDown = false;
			UE_LOG(LogTemp, Display, TEXT("Space pressed IsDown true, Gravity.Z=%f"), Gravity.Z);
		}
		else
		{
			Gravity = FVector(0.0f, 0.0f, 0.0f); 
			IsDown = true;
			UE_LOG(LogTemp, Display, TEXT("Space pressed IsDown false, Gravity.Z=%f"), Gravity.Z);
		}
		CanJump = false;
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("CanJump = false"));
}

void ABallPawn::CheckDead()
{
	check(GameInst)
	FVector CurrentLocation = GetActorLocation();
	if (CurrentLocation.Z < -255.0f || CurrentLocation.Z > 255.0f)
	{
		GameInst->SetIsDead(true);
		if (GameInst->GetMyScore() > GameInst->GetMyHighScore())
			GameInst->SetHighScore(GameInst->GetMyScore());
	}

}

void ABallPawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Display, TEXT("OnHit function was called"));
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		CanJump = true;
		//UE_LOG(LogTemp, Display, TEXT("CanJump = true"));
	}
}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABallPawn::ChangeFloor);
}

