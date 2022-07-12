// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "BallPawn.h"

// Sets default values
ABallPawn::ABallPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	BallMesh = CreateDefaultSubobject<USphereComponent>("BallMesh");
	SetRootComponent(BallMesh);
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetNotifyRigidBodyCollision(true);
	BallMesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	BallMesh->OnComponentHit.AddDynamic(this, &ABallPawn::OnHit);
}

// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	Pitch();
	Gravity = FVector(0.0, 0.0, 0.0);
	GameInst = Cast<UMyGameInstance>(GetGameInstance());



}

// Called every frame
void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	USphereComponent* prim = Cast<USphereComponent>(this->GetRootComponent());
	if(prim)
		prim->SetPhysicsLinearVelocity(Gravity, true);
	
	CheckDead();
}


void ABallPawn::Pitch() {

	CurrentRotation = GetActorRotation();
	Speed = Speed * -1;
	CurrentRotation.Pitch = FMath::Clamp(Speed, -10.0f, -1.0f);
	if (!CurrentRotation.IsZero()) {
		UE_LOG(LogTemp, Warning, TEXT("Pitch = %f"), GetActorRotation().Pitch);
	}
}
void ABallPawn::ChangeFloor()
{
	if (CanJump)
	{
		if (IsDown)
		{
			Gravity = FVector(0.0, 0.0, 5.0); 
			CanJump = false;
			IsDown = false;
		}
		else
		{
			Gravity = FVector(0.0, 0.0, 0.0); 
			CanJump = false;
			IsDown = true;
		}
	}
}

void ABallPawn::CheckDead()
{
	if (!GameInst)
		return;
	FVector CurrentLocation = GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("ViewSize.X=%f, ViewSize.Y=%f"), GameInst->GetMyViewSize().X, GameInst->GetMyViewSize().Y);
	if (CurrentLocation.Z < -255 || CurrentLocation.Z > 255)
	{
		GameInst->SetIsDead(true);
		if (GameInst->GetMyScore() > GameInst->GetMyHighScore())
			GameInst->SetHighScore(GameInst->GetMyScore());
	}

}

void ABallPawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		CanJump = true;
	}
}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABallPawn::ChangeFloor);
	//PlayerInputComponent->BindAxis("Jump1", this, &ABallPawn::ChangeFloor);
}

