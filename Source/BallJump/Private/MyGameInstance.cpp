#include "MyGameInstance.h"

void UMyGameInstance::CheckIfOutOfTheScreenAndDestroy(AActor* Object)
{
    if (!Object) return;
    FVector CurrentLocation = Object->GetActorLocation();
    
    if (CurrentLocation.X < -450.0f && !(Object->WasRecentlyRendered()))
        Object->Destroy();
}

void UMyGameInstance::HandleMovement(AActor* Object, double DeltaTime, bool cloud=false)
{
    FVector CurrentLocation = Object->GetActorLocation();
    CurrentLocation.X -= 20 * DeltaTime * (cloud ? static_cast<float>(Speed) / 2.0f : static_cast<float>(Speed));
    Object->SetActorLocation(CurrentLocation);
}
