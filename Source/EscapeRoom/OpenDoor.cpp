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
    
    Owner = GetOwner();
	
}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
    if (GetTotalMassOfActorsOnPlate() > MassTresholdForPressurePlate)
    {
        OnOpen.Broadcast();
    }
    else
    {
        OnClose.Broadcast();
    }
    
}


float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float TotalMass = 0;
    
    TArray<AActor*> OverlappingActors;
    // Find All Overlapping Actors
    PressurePlate->GetOverlappingActors(OverlappingActors);
    for (const auto& Actor : OverlappingActors) {
        UE_LOG(LogTemp, Warning, TEXT("%s on Pressure Plate"), *Actor->GetName());
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        
    }
    
    
    return TotalMass;
}



