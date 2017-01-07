// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeRoom.h"
#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation);
//    UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotations: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString())
    
    
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    // Draw a red trace
    DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, 0.f, 0.f, 10.f);
    
    /// Set up query parameters
    FCollisionQueryParams TraceParameters = (FName(TEXT("")), false, GetOwner());
    
    FHitResult FHit;
    FVector Start;
    FVector End;
    FCollisionObjectQueryParams ObjectQueryParams;
    // Line Trace (AKA ray-cast)
    GetWorld()->LineTraceSingleByObjectType(OUT FHit,
                                             PlayerViewPointLocation,
                                             LineTraceEnd,
                                             ECollisionChannel::ECC_PhysicsBody,
                                             TraceParameters
                                             );
    
    if (AActor * ActorHit = FHit.GetActor())
    {
        UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *ActorHit->GetName());
    }
    
    
    
}

