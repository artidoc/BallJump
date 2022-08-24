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
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetNotifyRigidBodyCollision(true);
	BallMesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	
}

// Called when the game starts or when spawned
void ABallPawn::BeginPlay()
{
	Super::BeginPlay();
	//Pitch();
	Gravity = FVector(0.0, 0.0, 0.0);
	GameInst = Cast<UMyGameInstance>(GetGameInstance());
	BallMesh->OnComponentHit.AddDynamic(this, &ABallPawn::OnHit);


}

// Called every frame
void ABallPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	prim = Cast<USphereComponent>(this->GetRootComponent());
	
	//change gravity direction
	if (prim)
	{
		//UE_LOG(LogTemp, Display, TEXT("Gravity X=%f,Y=%f,Z=%f"), Gravity.X, Gravity.Y, Gravity.Z);
		prim->SetPhysicsLinearVelocity(Gravity, true);
		//UE_LOG(LogTemp, Display, TEXT("PhysicsLinearVelocity X=%f,Y=%f,Z=%f"), prim->GetPhysicsLinearVelocity().X, prim->GetPhysicsLinearVelocity().Y, prim->GetPhysicsLinearVelocity().Z);
	}
	
	CheckDead();
}


void ABallPawn::Pitch() {

	CurrentRotation = GetActorRotation();
	Speed = Speed * -1;
	CurrentRotation.Pitch = FMath::Clamp(Speed, -10.0f, -1.0f);
	if (!CurrentRotation.IsZero()) {
		UE_LOG(LogTemp, Display, TEXT("Pitch = %f"), GetActorRotation().Pitch);
	}
}
void ABallPawn::ChangeFloor()
{
	if (CanJump)
	{
		//UE_LOG(LogTemp, Display, TEXT("CanJump = true"));
		if (IsDown)
		{
			Gravity = FVector(0.0, 0.0, 10.0); 
			IsDown = false;
			//UE_LOG(LogTemp, Display, TEXT("Space pressed IsDown true, Gravity.Z=%f"), Gravity.Z);
		}
		else
		{
			Gravity = FVector(0.0, 0.0, 0.0); 
			IsDown = true;
			//UE_LOG(LogTemp, Display, TEXT("Space pressed IsDown false, Gravity.Z=%f"), Gravity.Z);
		}
		
		CanJump = false;

		

	}
	else
		UE_LOG(LogTemp, Warning, TEXT("CanJump = false"));
}

void ABallPawn::CheckDead()
{
	if (!GameInst)
		return;
	FVector CurrentLocation = GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("ViewSize.X=%f, ViewSize.Y=%f"), GameInst->GetMyViewSize().X, GameInst->GetMyViewSize().Y);
	if (CurrentLocation.Z < -255 || CurrentLocation.Z > 255)
	{
		GameInst->SetIsDead(true);
		if (GameInst->GetMyScore() > GameInst->GetMyHighScore())
			GameInst->SetHighScore(GameInst->GetMyScore());
	}

}

void ABallPawn::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("OnHit function was called"));
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		CanJump = true;
		UE_LOG(LogTemp, Display, TEXT("CanJump = true"));
	}
}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABallPawn::ChangeFloor);
	//PlayerInputComponent->BindAxis("Jump1", this, &ABallPawn::ChangeFloor);
}

