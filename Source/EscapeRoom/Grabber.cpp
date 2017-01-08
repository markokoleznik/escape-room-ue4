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
    
    // Look for attached Physics Handle
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle)
    {
        
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Physics Component"), *GetOwner()->GetName())
    }
    
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Input Component found"))
        /// Bind the input axis
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName())
    }
    
	
}

void UGrabber::Release()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab Released"))
    
    PhysicsHandle->ReleaseComponent();
}

void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab Pressed"))
    auto HitResult = GetFirstPhysicsBodyInReach();
    
    auto ComponentToGrab = HitResult.GetComponent();
    
    auto ActorHit = HitResult.GetActor();
    
    if (ActorHit)
    {
        PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), FRotator::ZeroRotator);
    }
    
    
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    FVector LineTraceEnd = GetReachLineEnd();

    if (PhysicsHandle->GrabbedComponent)
    {
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }
    
    
}

FVector UGrabber::GetReachLineEnd()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
                                                               OUT PlayerViewPointLocation,
                                                               OUT PlayerViewPointRotation);
    //    UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotations: %s"), *PlayerViewPointLocation.ToString(), *PlayerViewPointRotation.ToString())
    
    
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
    return LineTraceEnd;
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    FVector LineTraceEnd = GetReachLineEnd();
    
    // Draw a red trace
//    DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor::Red, false, 0.f, 0.f, 10.f);
    
    /// Set up query parameters
    FCollisionQueryParams TraceParameters = (FName(TEXT("")), false, GetOwner());
    
    
    FHitResult FHit;
    FVector Start;
    FVector End;
    FCollisionObjectQueryParams ObjectQueryParams;
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
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
    return FHit;
}

