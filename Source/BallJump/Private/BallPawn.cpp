#include "BallPawn.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"

ABallPawn::ABallPawn()
{
    PrimaryActorTick.bCanEverTick = true;
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    BallMesh = CreateDefaultSubobject<USphereComponent>("BallMesh");
    SetRootComponent(BallMesh);
    BallMesh->SetSimulatePhysics(true);
    BallMesh->SetNotifyRigidBodyCollision(true);
    BallMesh->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
}

void ABallPawn::BeginPlay()
{
    Super::BeginPlay();
    GameInst = Cast<UMyGameInstance>(GetGameInstance());
    BallMesh->OnComponentHit.AddDynamic(this, &ABallPawn::OnHit);
}

void ABallPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    prim = Cast<USphereComponent>(this->GetRootComponent());

    check(prim);
    prim->AddForce(Gravity, NAME_None, true);
    CheckDead();
}

void ABallPawn::ActiveButton()
{
    if (!CanJump)
        return;
    if (IsDown)
        ChangeFloor(2500.0f, false);
    else
        ChangeFloor(0.0f, true);
    CanJump = false;
}

void ABallPawn::ChangeFloor(float num, bool Down)
{
    Gravity = FVector(0.0f, 0.0f, num);
    IsDown = Down;
    UE_LOG(LogTemp, Display, TEXT("Space pressed, Gravity.Z=%f"), Gravity.Z);
}

void ABallPawn::CheckDead()
{
    check(GameInst);
    FVector CurrentLocation = GetActorLocation();
    if (CurrentLocation.Z < -255.0f || CurrentLocation.Z > 255.0f)
    {
        GameInst->SetIsDead(true);
        if (GameInst->GetMyScore() > GameInst->GetMyHighScore()) 
            GameInst->SetHighScore(GameInst->GetMyScore());
    }
}

void ABallPawn::OnHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
        CanJump = true;
}

// Called to bind functionality to input
void ABallPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ABallPawn::ActiveButton);
}
