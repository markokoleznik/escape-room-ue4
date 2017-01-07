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
    }
}

void UOpenDoor::OpenDoor()
{
    
    AActor* Owner = GetOwner();
    
    FRotator Rotator = FRotator(0.0f, OpenAngle, 0.0f);
    
    Owner->SetActorRotation(Rotator);
    
    
}

