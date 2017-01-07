// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeRoom.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    Owner = GetOwner();

	// ...
//    OpenDoor();
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
    if (PressurePlate->IsOverlappingActor(ActorThatOpens))
    {
        OpenDoor();
        LastOpenDoorTime = GetWorld()->GetTimeSeconds();
    }
    
    // Check if it is time to close the door
    if (GetWorld()->GetTimeSeconds() - LastOpenDoorTime > DoorCloseDelay)
    {
        CloseDoor();
    }
    
}

void UOpenDoor::OpenDoor()
{
    FRotator Rotator = FRotator(0.0f, OpenAngle, 0.0f);
    Owner->SetActorRotation(Rotator);
}

void UOpenDoor::CloseDoor()
{
    FRotator Rotator = FRotator(0.0f, 180.0f, 0.0f);
    Owner->SetActorRotation(Rotator);
}



