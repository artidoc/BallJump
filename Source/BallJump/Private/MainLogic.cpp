#include "MainLogic.h"
#include "Kismet/GameplayStatics.h"

AMainLogic::AMainLogic()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AMainLogic::BeginPlay()
{
    Super::BeginPlay();

    GameInst = Cast<UMyGameInstance>(GetGameInstance());
    check(GameInst);
    ChangeScreenSize();
    GameInst->SetIsDead(false);
    GameInst->SetSpeed(0);
    check(GetWorld());
    GenerateOnStartCloud();
    if (UGameplayStatics::GetCurrentLevelName(this, true) == "GameMap")
        GenerateOnStartBlock();
}

void AMainLogic::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ChangeScreenSize();

    GenerateNewCloud();
    if (UGameplayStatics::GetCurrentLevelName(this, true) == "GameMap")
    {
        check(downBlockPointer && upBlockPointer);
        GenerateNewBlock(downBlockPointer, false);
        GenerateNewBlock(upBlockPointer, true);
        SpeedOnStart();
    }
    else
        GameInst->SetSpeed(7);
}

void AMainLogic::ChangeScreenSize()
{
    check(GameInst);
    UGameViewportClient* Viewport = GetWorld()->GetGameViewport();
    if (ViewSize.X != Viewport->Viewport->GetSizeXY().X || ViewSize.Y != Viewport->Viewport->GetSizeXY().Y)
    {
        ViewSize = Viewport->Viewport->GetSizeXY();
        GameInst->SetViewSize(ViewSize);
        UE_LOG(LogTemp, Display, TEXT("ScreenSize was changed"));
    }
}

void AMainLogic::GenerateOnStartCloud()
{
    FRotator Rotation = FRotator(0.0, 0.0, 0.0);
    FVector CloudLocation = FVector(-200.0f, 0.0f, 340.0f);
    cloudPointer = GetWorld()->SpawnActor(CloudSpawn, &CloudLocation, &Rotation);
}

void AMainLogic::GenerateOnStartBlock()
{
    FRotator Rotation = FRotator(0.0, 0.0, 0.0);
    FVector LocationDown = FVector(-450.0f, 0.0f, -250.0f);
    FVector LocationUp = FVector(300.0f, 0.0f, 250.0f);
    FTransform BlockTransform;

    BlockTransform.SetRotation(FQuat(Rotation));
    BlockTransform.SetScale3D(FVector(10.0f, 1.0f, 0.5f));
    BlockTransform.SetLocation(LocationDown);
    downBlockPointer = GetWorld()->SpawnActor(BlockSpawn, &BlockTransform);
    BlockTransform.SetLocation(LocationUp);
    upBlockPointer = GetWorld()->SpawnActor(BlockSpawn, &BlockTransform);

    GetWorldTimerManager().SetTimer(TimerHandle, this, &AMainLogic::OnTimerFired, TimerRate, true);
}

void AMainLogic::GenerateNewCloud()
{
    check(cloudPointer);
    FVector CloudLocation = cloudPointer->GetActorLocation();

    if (CloudLocation.X < ViewSize.X)
    {
        FVector CLoudVectorLocation = FVector(
            CloudLocation.X + FMath::RandRange(1000.0f, 1500.0f)
            , 0.0f
            , FMath::RandRange(-(ViewSize.Y / 2.0f), ViewSize.Y / 2.0f));

        FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
        cloudPointer = GetWorld()->SpawnActor(CloudSpawn, &CLoudVectorLocation, &Rotation);
    }
}

void AMainLogic::GenerateNewBlock(AActor*& Block, bool up)
{
    FVector BlockLocation = Block->GetActorLocation();
    FVector BlockScale = Block->GetActorScale();

    //check if right part of block is on the screen
    if ((BlockLocation.X + (BlockScale.X * 25.0f)) < static_cast<float>(ViewSize.X))
    {
        FTransform BlockTransform;
        float ScaleX = NewScaleX();
        BlockTransform.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
        BlockTransform.SetScale3D(FVector(ScaleX, 1.0f, 0.5f));

        float TempLocation = BlockLocation.X + (BlockScale.X * 25.0f) + (BlockTransform.GetScale3D().X * 25.0f) + 1000.0f;

        FVector NewLocation = FVector(TempLocation, 0.0f, (up ? 250.0f : -250.0f));
        BlockTransform.SetLocation(NewLocation);
        
        Block = GetWorld()->SpawnActor(BlockSpawn, &BlockTransform);
    }
}

float AMainLogic::NewScaleX()
{
    return 10.0f * (100.0f - Speed * 2.0f) / 100.0f;
}

void AMainLogic::SpeedOnStart()
{
    int32 timeFromStartInSec = static_cast<int32>(GetWorld()->GetTimeSeconds());
    if (timeFromStartInSec > 0 && timeFromStartInSec <= 5) SpeedCalc();
    ScoreCalc();
}

void AMainLogic::SpeedCalc()
{
    Speed++;
    Speed = SpeedClamp(Speed);
    GameInst->SetSpeed(Speed);
}

void AMainLogic::ScoreCalc()
{
    int32 Score = GameInst->GetMyScore();
    Score++;
    Score = static_cast<int32>(SpeedClamp(Score));
    GameInst->SetScore(Score);
}

float AMainLogic::SpeedClamp(float Speedtmp)
{
    float TimeSec = GetWorld()->GetTimeSeconds();
    return FMath::Clamp(Speedtmp, 0.0f, TimeSec);
}

void AMainLogic::OnTimerFired()
{
    Speed+=0.05f;
    Speed = FMath::Clamp(Speed, 0.0f, 50.0f);
    check(GameInst);
    GameInst->SetSpeed(Speed);
}