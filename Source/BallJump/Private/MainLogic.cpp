// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "MainLogic.h"

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
	
	//get screen size
	ScreenSize();

	GameInst = Cast<UMyGameInstance>(GetGameInstance());

	if (GetWorld())
	{
		//spawn 3 new blocks - up, down and cloud
		FRotator Rotation = FRotator(0.0, 0.0, 0.0);
		
		//if level GameMap - spawn up and down blocks
		if (UGameplayStatics::GetCurrentLevelName(this, true) == "GameMap")
		{
			FVector LocationDown = FVector(-450.0, 0.0, -250.0);
			FVector LocationUp = FVector(250.0, 0.0, 250.0);
			FTransform DownBlockTransform;
			DownBlockTransform.SetRotation(FQuat(Rotation));
			DownBlockTransform.SetScale3D(FVector(10.0f, 1.0f, 0.5f));
			DownBlockTransform.SetLocation(LocationDown);
			FTransform UpBlockTransform;
			UpBlockTransform.SetRotation(FQuat(Rotation));
			UpBlockTransform.SetScale3D(FVector(10.0f, 1.0f, 0.5f));
			UpBlockTransform.SetLocation(LocationUp);

			DownBlock = GetWorld()->SpawnActor(BlockSpawn, &DownBlockTransform);
			UpBlock = GetWorld()->SpawnActor(BlockSpawn, &UpBlockTransform);
			GameInst->SetSpeed(0);
			GetWorldTimerManager().SetTimer(TimerHandle, this, &AMainLogic::OnTimerFired, TimerRate, true);
		}
		FVector CloudLocation = FVector(0.0, 0.0, 340.0);
		CloudBP = GetWorld()->SpawnActor(CloudSpawn, &CloudLocation, &Rotation);

	}
}

// Called every frame
void AMainLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckAndSpawnCloud();
	if (UGameplayStatics::GetCurrentLevelName(this, true) == "GameMap")
	{
		CheckAndSpawnBlock();
		int32 TimeSec = static_cast<int32>(GetWorld()->GetTimeSeconds());
		if (TimeSec > 0 && TimeSec <= 5)
			SpeedCalc();
	}
	else
		GameInst->SetSpeed(7);
}

void AMainLogic::ScreenSize()
{
	UGameViewportClient* Viewport = GetWorld()->GetGameViewport();
	ViewSize = Viewport->Viewport->GetSizeXY();

}

void AMainLogic::CheckAndSpawnCloud()
{
	if (CloudBP)
	{
		//get location and scale of spawned blocks
		FVector CloudLocation = CloudBP->GetActorLocation();

		//spawn new blocks while the end of screen
		if (CloudLocation.X + 150 < ViewSize.X)
		{
			FRotator Rotation = FRotator(0.0, 0.0, 0.0);
			
			//calculate of location of new cube block
			double NewCloudLocation = CloudLocation.X + 150 + 150 + FMath::RandRange(400.0f, 600.0f);

			

			//Set new location
			FVector CLoudVectorLocation = FVector(NewCloudLocation, 0.0, FMath::RandRange(-(ViewSize.Y / 2), ViewSize.Y / 2));

			//spawn new blocks
			CloudBP = GetWorld()->SpawnActor(CloudSpawn, &CLoudVectorLocation, &Rotation);
		}


	}
	else 
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("CloudBP are nullptr")));
}

void AMainLogic::CheckAndSpawnBlock()
{
	//if ptr for blocks are not empty - spawn new blocks
	if (DownBlock && UpBlock)
	{
		//get location and scale of spawned blocks
		FVector DownBlockLocation = DownBlock->GetActorLocation();
		FVector DownBlockScale = DownBlock->GetActorScale();
		FVector UpBlockLocation = UpBlock->GetActorLocation();
		FVector UpBlockScale = UpBlock->GetActorScale();
		
		//spawn new blocks while the end of screen
		if (DownBlockLocation.X + ((DownBlockScale.X * 50) / 2) < ViewSize.X && UpBlockLocation.X + ((UpBlockScale.X * 50) / 2) < ViewSize.X)
		{
			//set rotation and scale of new cube block
			FTransform DownBlockTransform;
			FTransform UpBlockTransform;
			
			FRotator Rotation = FRotator(0.0, 0.0, 0.0);
			DownBlockTransform.SetRotation(FQuat(Rotation));
			DownBlockTransform.SetScale3D(FVector(10.0f, 1.0f, 0.5f));
			UpBlockTransform.SetRotation(FQuat(Rotation));
			UpBlockTransform.SetScale3D(FVector(10.0f, 1.0f, 0.5f));

			//calculate of location of new cube block
			double TempDownLocation = DownBlockLocation.X + (DownBlockScale.X * 25.0) + (DownBlockTransform.GetScale3D().X * 25.0)+ 1000.0f;
			double TempUpLocation = UpBlockLocation.X + (UpBlockScale.X * 25.0) + (UpBlockTransform.GetScale3D().X * 25.0)+ 1000.0f;
			
			//Set new location
			FVector TempLocationDown = FVector(TempDownLocation, 0.0, -250.0);
			FVector TempLocationUp = FVector(TempUpLocation, 0.0, 250.0);
			DownBlockTransform.SetLocation(TempLocationDown);
			UpBlockTransform.SetLocation(TempLocationUp);

			//spawn new blocks
			DownBlock = GetWorld()->SpawnActor(BlockSpawn, &DownBlockTransform);
			UpBlock = GetWorld()->SpawnActor(BlockSpawn, &UpBlockTransform);
		}
		

	}
	else if (DownBlock && !UpBlock)
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UpBlock are nullptr")));
	else if (!DownBlock && UpBlock)
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("DownBlock are nullptr")));
	else
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("DownBlock and UpBlock are nullptr")));
}
/*
void AMainLogic::SpawnActors(TSubclassOf<ABlock> ActorSpawn, FTransform& TransformDown, FTransform& TransformUp)
{
	DownBlock = GetWorld()->SpawnActor(ActorSpawn, &TransformDown);
	//UpBlock = GetWorld()->SpawnActor(ActorSpawn, &LocationUp, &Rotation);
}*/
void AMainLogic::SpawnActors(TSubclassOf<ACloud> ActorSpawn, FVector& Location, FRotator& Rotation)
{
	CloudBP = GetWorld()->SpawnActor(ActorSpawn, &Location, &Rotation);
}


void AMainLogic::SpeedCalc()
{

	Speed++;
	Speed = SpeedClamp(Speed);
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Speed=%i"), Speed));
	if (GameInst) 
		GameInst->SetSpeed(Speed);
	else
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GameInst is nullptr")));
}

int32 AMainLogic::SpeedClamp(int32 Speedtmp)
{
	int32 TimeSec = static_cast<int32>(GetWorld()->GetTimeSeconds());
	return FMath::Clamp(Speedtmp, 0, TimeSec);
}

void AMainLogic::OnTimerFired()
{
	Speed++;
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Speed=%i"), Speed));
	if (GameInst)
		GameInst->SetSpeed(Speed);
	else
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GameInst is nullptr")));
}