// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnDoorEvent );


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
    
    UPROPERTY(BlueprintAssignable)
    FOnDoorEvent OnOpen;
    
    UPROPERTY(BlueprintAssignable)
    FOnDoorEvent OnClose;

private:
    
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;
    
    AActor * Owner = nullptr;
    
    UPROPERTY(EditAnywhere)
    float MassTresholdForPressurePlate = 50.0f;
    
    float GetTotalMassOfActorsOnPlate();
		
	
};
