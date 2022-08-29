// Fill out your copyright notice in the Description page of Project Settings.

#include "MainLogic.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainLogic::AMainLogic()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainLogic::BeginPlay()
{
    Super::BeginPlay();

    GameInst = Cast<UMyGameInstance>(GetGameInstance());

    // get screen size
    ScreenSize();

    check(GameInst);
    GameInst->SetIsDead(false);
    GameInst->SetSpeed(0);

    check(GetWorld());

    // spawn 3 new blocks - up, down and cloud
    FRotator Rotation = FRotator(0.0, 0.0, 0.0);

    // if level GameMap - spawn up and down blocks
    if (UGameplayStatics::GetCurrentLevelName(this, true) == "GameMap")
    {
        FVector LocationDown = FVector(-450.0f, 0.0f, -250.0f);
        FVector LocationUp = FVector(350.0f, 0.0f, 250.0f);
        FTransform BlockTransform;
        //Transformation for down block
        BlockTransform.SetRotation(FQuat(Rotation));
        BlockTransform.SetScale3D(FVector(10.0f, 1.0f, 0.5f));
        BlockTransform.SetLocation(LocationDown);
        DownBlock = GetWorld()->SpawnActor(BlockSpawn, &BlockTransform);

        //change location for up block
        BlockTransform.SetLocation(LocationUp);
        UpBlock = GetWorld()->SpawnActor(BlockSpawn, &BlockTransform);

        GetWorldTimerManager().SetTimer(TimerHandle, this, &AMainLogic::OnTimerFired, TimerRate, true);
    }
    FVector CloudLocation = FVector(-200.0f, 0.0f, 340.0f);
    CloudBP = GetWorld()->SpawnActor(CloudSpawn, &CloudLocation, &Rotation);
}

// Called every frame
void AMainLogic::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CloudBP = GenerateNewCloud(CloudBP);
    if (UGameplayStatics::GetCurrentLevelName(this, true) == "GameMap")
    {
        /// Spawn new blocks
        check(DownBlock && UpBlock);
        DownBlock = GenerateNewBlock(DownBlock, false);
        UpBlock = GenerateNewBlock(UpBlock, true);
        /// End
        int32 TimeSec = static_cast<int32>(GetWorld()->GetTimeSeconds());
        if (TimeSec > 0 && TimeSec <= 5) SpeedCalc();
        ScoreCalc();
    }
    else
    {
        check(GameInst);
        GameInst->SetSpeed(7);
    }
}

void AMainLogic::ScreenSize()
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

AActor* AMainLogic::GenerateNewCloud(AActor* Cloud)
{
    check(Cloud);
    // get location and scale of spawned blocks
    FVector CloudLocation = Cloud->GetActorLocation();

    // spawn new blocks while the end of screen
    if (CloudLocation.X < ViewSize.X)
    {
        // Set new location
        FVector CLoudVectorLocation = FVector(
            CloudLocation.X + FMath::RandRange(600.0f, 1000.0f)  // calculate location of new cloud
            ,0.0f
            , FMath::RandRange(-(ViewSize.Y / 2.0f), ViewSize.Y / 2.0f));

        FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
        // spawn new blocks
        return GetWorld()->SpawnActor(CloudSpawn, &CLoudVectorLocation, &Rotation);
    }
    return Cloud;
}
AActor* AMainLogic::GenerateNewBlock(AActor* Block, bool up)
{
    // set rotation and scale of new block
    FVector BlockLocation = Block->GetActorLocation();
    FVector BlockScale = Block->GetActorScale();

    //check if right part of block is on the screen
    if ((BlockLocation.X + (BlockScale.X * 25.0f)) < static_cast<float>(ViewSize.X))
    {
        FTransform BlockTransform;
        BlockTransform.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
        BlockTransform.SetScale3D(FVector(10.0f, 1.0f, 0.5f));

        // calculate of location of new cube block
        float TempLocation = BlockLocation.X + (BlockScale.X * 25.0f) + (BlockTransform.GetScale3D().X * 25.0f) + 1000.0f;

        // Set new location
        FVector NewLocation = FVector(TempLocation, 0.0f, (up ? 250.0f : -250.0f));
        BlockTransform.SetLocation(NewLocation);
        
        //return ptr for new spawned object
        return GetWorld()->SpawnActor(BlockSpawn, &BlockTransform);
    }
    return Block;
}

void AMainLogic::SpeedCalc()
{
    Speed++;
    Speed = SpeedClamp(Speed);
    check(GameInst);
    GameInst->SetSpeed(Speed);
}

void AMainLogic::ScoreCalc()
{
    Score++;
    Score = SpeedClamp(Score);
    check(GameInst);
    GameInst->SetScore(Score);
}

int32 AMainLogic::SpeedClamp(int32 Speedtmp)
{
    int32 TimeSec = static_cast<int32>(GetWorld()->GetTimeSeconds());
    return FMath::Clamp(Speedtmp, 0, TimeSec);
}

void AMainLogic::OnTimerFired()
{
    Speed++;
    check(GameInst);
    GameInst->SetSpeed(Speed);

    ScreenSize();
}
