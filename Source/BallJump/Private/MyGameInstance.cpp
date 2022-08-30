// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

void UMyGameInstance::CheckToDestroy(AActor* Object)
{
    // Get screen size
    FVector CurrentLocation = Object->GetActorLocation();
    // if block out of the screen - destroy
    
    if (CurrentLocation.X < -450.0f && !(Object->WasRecentlyRendered()))
    {
        Object->Destroy();
    }
}

void UMyGameInstance::HandleMovement(AActor* Object, double DeltaTime, bool cloud=false)
{
    FVector CurrentLocation = Object->GetActorLocation();
    CurrentLocation.X -= 20 * DeltaTime * (cloud ? static_cast<float>(GetMySpeed()) / 2.0f
                                                      : static_cast<float>(GetMySpeed()));
    Object->SetActorLocation(CurrentLocation);
}
